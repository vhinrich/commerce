<?php

/**
 * @file
 * Class and methods for interacting with the Marketo SOAP API.
 */

/**
 * Marketo Interface
 */
interface MarketoInterface {

  /**
   * Retrieves list of defined fields.
   */
  public function getFields();

  /**
   * Retrieves lead information.
   * 
   * @param string $key
   *   Lead Key, typically email address
   * @param string $type
   *   Lead key type, auto-detection attempted if not supplied
   */
  public function getLead($key, $type);

  /**
   * Retrieves lead activity information.
   * 
   * @param string $key
   *   Lead Key, typically email address
   * @param string $type
   *   Lead key type, auto-detection attempted if not supplied
   */
  public function getLeadActivity($key, $type);

  /**
   * Inserts or updates a lead.
   * 
   * @param array $lead
   *   Key value pairs to be associated with a lead
   * @param string $key
   *   Lead Key, typically email address
   * @param object $cookie
   *   Marketo cookie information
   * @param array $options
   *   Array of additional options to configure lead syncing
   */
  public function syncLead($lead, $key, $cookie, $options);
}

/**
 * Marketo Client
 */
class MarketoClient implements MarketoInterface {

  // http://app.marketo.com/soap/mktows/2_0?WSDL
  protected $userId;
  protected $encryptionKey;
  protected $endpoint;

  /**
   * Constructor for MarketoClient class.
   * 
   * @param string $user_id
   *   A User ID (aka Access Key) defined in Marketo admin
   * @param string $encryption_key
   *   A shared secret-key (aka Encryption Key) defined in Marketo admin
   * @param string $endpoint
   *   SOAP endpoint URL
   * @param array $options
   *   Optional array of SoapClient options 
   */
  public function __construct($user_id, $encryption_key, $endpoint, $options = array()) {
    $this->userId = $user_id;
    $this->encryptionKey = $encryption_key;
    $this->endpoint = $endpoint;

    $wsdl = $this->endpoint . '?WSDL';

    $default_options = array(
      "connection_timeout" => 20,
      "location" => $this->endpoint,
    );
    $soap_options = array_merge($default_options, $options);

    $this->client = new SoapClient($wsdl, $soap_options);
  }

  /**
   * Builds Marketo authentication header.
   * 
   * @return \SoapHeader
   *   Marketo authentication header
   */
  protected function authenticationHeader() {
    $timestamp = date("c");
    $encrypt_string = $timestamp . $this->userId;
    $signature = hash_hmac('sha1', $encrypt_string, $this->encryptionKey);

    $data = new stdClass();
    $data->mktowsUserId = $this->userId;
    $data->requestSignature = $signature;
    $data->requestTimestamp = $timestamp;

    $header = new SoapHeader('http://www.marketo.com/mktows/', 'AuthenticationHeader', $data);

    return $header;
  }

  /**
   * Determines lead key type for a given key.
   * 
   * @param string $key
   *   The key to examine
   * 
   * @return string
   *   Lead key type
   */
  protected function keyType($key) {
    if (filter_var($key, FILTER_VALIDATE_EMAIL)) {
      $type = 'EMAIL';
    }
    elseif (is_int($key) || (is_string($key) && ctype_digit($key))) {
      $type = 'IDNUM';
    }
    elseif (filter_var($key, FILTER_VALIDATE_REGEXP, array('options' => array('regexp' => '/^id:.*&token:.*/')))) {
      $type = 'COOKIE';
    }
    else {
      $type = 'UNKNOWN';
    }

    return $type;
  }

  /**
   * Sends request to Marketo.
   * 
   * @param string $operation
   *   The operation to execute
   * @param array $params
   *   Parameters to be sent with the request
   * 
   * @return object
   *   Response object
   */
  protected function request($operation, $params) {
    return $this->client->__soapCall(
        $operation, array($params), array(), $this->authenticationHeader()
    );
  }

  /**
   * Returns the XML sent in the last SOAP request.
   * 
   * @return string
   */
  public function __getLastRequest() {
    return $this->client->__getLastRequest();
  }

  /**
   * Returns the XML received in the last SOAP response.
   *
   * @return string
   */
  public function __getLastResponse() {
    return $this->client->__getLastResponse();
  }

  /**
   * {@inheritdoc}
   */
  public function getLead($key, $type = NULL) {
    $lead = new stdClass();
    $lead->leadKey = new stdClass();
    $lead->leadKey->keyType = (is_null($type)) ? $this->keyType($key) : strtoupper($type);
    $lead->leadKey->keyValue = $key;

    try {
      $result = $this->request('getLead', $lead);
      $leads = $this->prepareLeadResults($result);
    }
    catch (Exception $e) {

      if (isset($e->detail->serviceException->code) && $e->detail->serviceException->code == MarketoError::ERR_LEAD_NOT_FOUND) {
        // No leads were found.
        $leads = array();
      }
      else {
        throw new Exception($e);
      }
    }

    return $leads;
  }

  /**
   * {@inheritdoc}
   */
  public function getLeadActivity($key, $type = NULL) {
    $lead = new stdClass();
    $lead->leadKey = new stdClass();
    $lead->leadKey->keyType = (is_null($type)) ? $this->keyType($key) : strtoupper($type);
    $lead->leadKey->keyValue = $key;
    $lead->activityFilter = new stdClass();
    $lead->startPosition = new stdClass();
    $lead->batchSize = 100;

    try {
      $result = $this->request('getLeadActivity', $lead);
      $activity = $this->prepareLeadActivityResults($result);
    }
    catch (Exception $e) {

      if (isset($e->detail->serviceException->code) && $e->detail->serviceException->code == MarketoError::ERR_LEAD_NOT_FOUND) {
        // No leads were found.
        $activity = array();
      }
      else {
        throw new Exception($e);
      }
    }

    return $activity;
  }

  /**
   * {@inheritdoc}
   */
  public function getFields() {
    $params = array(
      'objectName' => 'LeadRecord',
    );
    try {
      $result = $this->request('describeMObject', $params);
      $fields = $this->prepareFieldResults($result);
    }
    catch (Exception $e) {
      $fields = array();
    }

    return $fields;
  }

  /**
   * {@inheritdoc}
   */
  public function syncLead($lead, $key = NULL, $cookie = NULL, $options = array()) {
    // Merge default options.
    $options += array(
      'returnLead' => FALSE,
      'extendedResponse' => FALSE,
    );

    $params = new stdClass();
    $params->marketoCookie = $cookie;
    $params->returnLead = $options['returnLead'];
    $params->leadRecord = $this->leadRecord($lead, $key);
    $ret = array(
      'success' => FALSE,
      'result' => NULL,
    );

    try {
      $ret['result'] = $this->request('syncLead', $params);
      $ret['success'] = TRUE;
    }
    catch (Exception $e) {
      $ret['result'] = $e->getMessage();
      $ret['success'] = FALSE;
    }
    return ($options['extendedResponse']) ? $ret : $ret['result'];
  }

  /**
   * Converts response into a more useful structure.
   * 
   * @param object $data
   *   LeadRecord object definition
   * 
   * @return array
   *   Key value pairs of fields
   */
  protected function prepareFieldResults($data) {
    $fields = array();

    foreach ($data->result->metadata->fieldList->field as $field) {
      $fields[$field->name] = $field->displayName;
    }

    return $fields;
  }

  /**
   * Creates proper structure for submitting a lead.
   * 
   * @param array $attributes
   *   Key value pairs to be associated withi this lead
   * @param string $key
   *   Lead Key
   * 
   * @return \stdClass
   *   Lead Record
   */
  protected function leadRecord($attributes, $key = NULL) {
    $record = new stdClass();

    if ($key) {
      if (is_numeric($key)) {
        $record->Id = $key;
      }
      else {
        $record->Email = $key;
      }
    }

    $record->leadAttributeList = new stdClass();
    $record->leadAttributeList->attribute = array();

    foreach ($attributes as $attribute => $value) {
      $lead_attribute = new stdClass();
      $lead_attribute->attrName = $attribute;
      $lead_attribute->attrValue = $value;

      array_push($record->leadAttributeList->attribute, $lead_attribute);
    }

    return $record;
  }

  /**
   * Parses lead results into a more useful format.
   * 
   * @param object $marketo_result
   *   SOAP response
   * 
   * @return array
   *   An array of objects defining lead data
   */
  protected function prepareLeadResults($marketo_result) {
    if ($marketo_result->result->count == 1) {
      $leads[] = $marketo_result->result->leadRecordList->leadRecord;
    }
    elseif ($marketo_result->result->count > 1) {
      $leads = $marketo_result->result->leadRecordList->leadRecord;
    }
    else {
      $leads = array();
    }

    foreach ($leads as &$lead) {
      $lead->attributes = array();
      foreach ($lead->leadAttributeList->attribute as $attribute) {
        $lead->attributes[$attribute->attrName] = $attribute->attrValue;
      }
      unset($lead->leadAttributeList);
    }

    return $leads;
  }

  /**
   * Parses lead activity results into a more useful format.
   * 
   * @param object $marketo_result
   *   SOAP response
   * 
   * @return array
   *   An array of objects defining lead activity data
   */
  protected function prepareLeadActivityResults($marketo_result) {
    if ($marketo_result->leadActivityList->returnCount > 1) {
      $activity = $marketo_result->leadActivityList->activityRecordList->activityRecord;
    }
    elseif ($marketo_result->leadActivityList->returnCount == 1) {
      $activity[] = $marketo_result->leadActivityList->activityRecordList->activityRecord;
    }
    else {
      $activity = array();
    }

    foreach ($activity as &$event) {
      $event->attributes = array();
      foreach ($event->activityAttributes->attribute as $attribute) {
        $event->attributes[$attribute->attrName] = $attribute->attrValue;
      }
      unset($event->activityAttributes);
    }

    return $activity;
  }

}

class MarketoError {

  const ERR_SEVERE_INTERNAL_ERROR = 10001;
  const ERR_INTERNAL_ERROR = 20011;
  const ERR_REQUEST_NOT_UNDERSTOOD = 20012;
  const ERR_ACCESS_DENIED = 20013;
  const ERR_AUTH_FAILED = 20014;
  const ERR_REQUEST_LIMIT_EXCEEDED = 20015;
  const ERR_REQ_EXPIRED = 20016;
  const ERR_INVALID_REQ = 20017;
  const ERR_BAD_ENCODING = 20018;
  const ERR_UNSUPPORTED_OP = 20019;
  const ERR_LEAD_KEY_REQ = 20101;
  const ERR_LEAD_KEY_BAD = 20102;
  const ERR_LEAD_NOT_FOUND = 20103;
  const ERR_LEAD_DETAIL_REQ = 20104;
  const ERR_LEAD_ATTRIB_BAD = 20105;
  const ERR_LEAD_SYNC_FAILED = 20106;
  const ERR_ACTIVITY_KEY_BAD = 20107;
  const ERR_PARAMETER_REQ = 20109;
  const ERR_PARAMETER_BAD = 20110;
  const ERR_LIST_NOT_FOUND = 20111;
  const ERR_CAMP_NOT_FOUND = 20113;
  const ERR_BAD_PARAMETER = 20114;
  const ERR_BAD_STREAM_POS = 20122;
  const ERR_STREAM_AT_END = 20123;

}

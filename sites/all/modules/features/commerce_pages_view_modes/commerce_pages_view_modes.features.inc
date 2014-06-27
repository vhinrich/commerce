<?php
/**
 * @file
 * commerce_pages_view_modes.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function commerce_pages_view_modes_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

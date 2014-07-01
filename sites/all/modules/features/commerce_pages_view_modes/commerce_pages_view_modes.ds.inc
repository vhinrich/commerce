<?php
/**
 * @file
 * commerce_pages_view_modes.ds.inc
 */

/**
 * Implements hook_ds_view_modes_info().
 */
function commerce_pages_view_modes_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'big_teaser';
  $ds_view_mode->label = 'Big Teaser';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['big_teaser'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'cart_product';
  $ds_view_mode->label = 'Cart Product';
  $ds_view_mode->entities = array(
    'commerce_product' => 'commerce_product',
  );
  $export['cart_product'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'featured';
  $ds_view_mode->label = 'Featured';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['featured'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'small_teaser';
  $ds_view_mode->label = 'Small Teaser';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['small_teaser'] = $ds_view_mode;

  return $export;
}

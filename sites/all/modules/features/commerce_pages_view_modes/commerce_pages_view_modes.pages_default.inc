<?php
/**
 * @file
 * commerce_pages_view_modes.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function commerce_pages_view_modes_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'home';
  $page->task = 'page';
  $page->admin_title = 'Home';
  $page->admin_description = '';
  $page->path = 'home';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_home_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'home';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
        ),
        'parent' => NULL,
        'class' => '',
        'column_class' => '',
        'row_class' => '',
        'region_class' => '',
        'no_scale' => FALSE,
        'fixed_width' => '',
        'column_separation' => '0em',
        'region_separation' => '0em',
        'row_separation' => '0em',
      ),
      'main' => array(
        'type' => 'column',
        'width' => 100,
        'width_type' => '%',
        'children' => array(
          0 => 2,
          1 => 'main-row',
          2 => 1,
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'center',
          1 => 'right',
        ),
        'parent' => 'main',
        'class' => 'row',
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'Main',
        'width' => '70.1758178411875',
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => 'col-sm-9',
      ),
      'right' => array(
        'type' => 'region',
        'title' => 'Right',
        'width' => '29.82418215881251',
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => 'col-sm-3',
      ),
      1 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'footer_main',
        ),
        'parent' => 'main',
        'class' => 'row',
      ),
      2 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'top_main',
        ),
        'parent' => 'main',
        'class' => 'row',
      ),
      'top_main' => array(
        'type' => 'region',
        'title' => 'Top Main',
        'width' => 100,
        'width_type' => '%',
        'parent' => '2',
        'class' => 'col-sm-12',
      ),
      'footer_main' => array(
        'type' => 'region',
        'title' => 'Footer Main',
        'width' => 100,
        'width_type' => '%',
        'parent' => '1',
        'class' => 'col-sm-12',
      ),
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'right' => NULL,
      'top_main' => NULL,
      'footer_main' => NULL,
    ),
    'top_main' => array(
      'style' => 'default',
    ),
    'center' => array(
      'style' => 'default',
    ),
    'right' => array(
      'style' => 'default',
    ),
    'footer_main' => array(
      'style' => 'default',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '7c4ebf4c-23ca-4a0d-9700-f33d31a23b7c';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-66459695-71bb-4c86-8a7c-ede9bcf005c8';
    $pane->panel = 'center';
    $pane->type = 'views_panes';
    $pane->subtype = 'product_displays-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '66459695-71bb-4c86-8a7c-ede9bcf005c8';
    $display->content['new-66459695-71bb-4c86-8a7c-ede9bcf005c8'] = $pane;
    $display->panels['center'][0] = 'new-66459695-71bb-4c86-8a7c-ede9bcf005c8';
    $pane = new stdClass();
    $pane->pid = 'new-9dd7fd68-762e-4bca-b253-bf793aa1290d';
    $pane->panel = 'center';
    $pane->type = 'views_panes';
    $pane->subtype = 'product_displays-panel_pane_2';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '9dd7fd68-762e-4bca-b253-bf793aa1290d';
    $display->content['new-9dd7fd68-762e-4bca-b253-bf793aa1290d'] = $pane;
    $display->panels['center'][1] = 'new-9dd7fd68-762e-4bca-b253-bf793aa1290d';
    $pane = new stdClass();
    $pane->pid = 'new-2c042796-1caf-464d-9d54-02f3e425dc64';
    $pane->panel = 'right';
    $pane->type = 'block';
    $pane->subtype = 'system-user-menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '2c042796-1caf-464d-9d54-02f3e425dc64';
    $display->content['new-2c042796-1caf-464d-9d54-02f3e425dc64'] = $pane;
    $display->panels['right'][0] = 'new-2c042796-1caf-464d-9d54-02f3e425dc64';
    $pane = new stdClass();
    $pane->pid = 'new-5738e6da-b630-4190-b104-b43e6663a902';
    $pane->panel = 'right';
    $pane->type = 'block';
    $pane->subtype = 'commerce_cart-cart';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '5738e6da-b630-4190-b104-b43e6663a902';
    $display->content['new-5738e6da-b630-4190-b104-b43e6663a902'] = $pane;
    $display->panels['right'][1] = 'new-5738e6da-b630-4190-b104-b43e6663a902';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['home'] = $page;

  return $pages;

}

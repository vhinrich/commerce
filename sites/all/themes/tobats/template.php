<?php

/**
 * @file
 * template.php
 */

/**
 * implement template_preprocess_node
 */
function tobats_preprocess_node(&$variables){
	$variables['classes_array'][] = 'node-' . $variables['view_mode'];
	$variables['theme_hook_suggestions'][] = 'node__' . $variables['type'] . '__' . $variables['view_mode'];
}
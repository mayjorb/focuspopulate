<?php
/**
 * @file
 * focuspopulate.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function focuspopulate_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'populatedatabase';
  $view->description = 'displays the closest shops to a users location';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Focus Populate Database';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Populate';
  $handler->display->display_options['css_class'] = 'gozulla-directory';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    4 => '4',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Find Me';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  /* Field: location nid */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['ui_name'] = 'location nid';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid_1']['node_in_colorbox_width'] = '600';
  $handler->display->display_options['fields']['nid_1']['node_in_colorbox_height'] = '600';
  /* Field: Content: Sports */
  $handler->display->display_options['fields']['field_sport_type']['id'] = 'field_sport_type';
  $handler->display->display_options['fields']['field_sport_type']['table'] = 'field_data_field_sport_type';
  $handler->display->display_options['fields']['field_sport_type']['field'] = 'field_sport_type';
  $handler->display->display_options['fields']['field_sport_type']['label'] = '';
  $handler->display->display_options['fields']['field_sport_type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_sport_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sport_type']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_sport_type']['delta_offset'] = '0';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['text'] = '[ edit ]';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h3';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Field: Address */
  $handler->display->display_options['fields']['field_address']['id'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address']['field'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['label'] = '';
  $handler->display->display_options['fields']['field_address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: Proximity: Distance */
  $handler->display->display_options['fields']['distance']['id'] = 'distance';
  $handler->display->display_options['fields']['distance']['table'] = 'openlayers_proximity';
  $handler->display->display_options['fields']['distance']['field'] = 'distance';
  $handler->display->display_options['fields']['distance']['label'] = '';
  $handler->display->display_options['fields']['distance']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['distance']['hide_empty'] = 1;
  $handler->display->display_options['fields']['distance']['set_precision'] = 1;
  $handler->display->display_options['fields']['distance']['precision'] = '1';
  $handler->display->display_options['fields']['distance']['location_provider'] = 'circle';
  /* Sort criterion: Proximity: Distance */
  $handler->display->display_options['sorts']['distance']['id'] = 'distance';
  $handler->display->display_options['sorts']['distance']['table'] = 'openlayers_proximity';
  $handler->display->display_options['sorts']['distance']['field'] = 'distance';
  $handler->display->display_options['sorts']['distance']['location_provider'] = 'circle';
  /* Contextual filter: Content: Has taxonomy term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gozullalocation' => 'gozullalocation',
  );
  /* Filter criterion: Proximity: Great-circle */
  $handler->display->display_options['filters']['circle']['id'] = 'circle';
  $handler->display->display_options['filters']['circle']['table'] = 'openlayers_proximity';
  $handler->display->display_options['filters']['circle']['field'] = 'circle';
  $handler->display->display_options['filters']['circle']['value']['value'] = '50';
  $handler->display->display_options['filters']['circle']['value']['location'] = 'Newport, OR';
  $handler->display->display_options['filters']['circle']['value']['node'] = '32745';
  $handler->display->display_options['filters']['circle']['expose']['operator_id'] = 'circle_op';
  $handler->display->display_options['filters']['circle']['expose']['operator'] = 'circle_op';
  $handler->display->display_options['filters']['circle']['expose']['identifier'] = 'circle';
  $handler->display->display_options['filters']['circle']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['circle']['expose']['use_unit'] = 0;
  $handler->display->display_options['filters']['circle']['expose']['use_location'] = 1;
  $handler->display->display_options['filters']['circle']['expose']['use_node'] = 0;
  /* Filter criterion: Content: gozulla sport (field_gozulla_sport) */
  $handler->display->display_options['filters']['field_gozulla_sport_tid']['id'] = 'field_gozulla_sport_tid';
  $handler->display->display_options['filters']['field_gozulla_sport_tid']['table'] = 'field_data_field_gozulla_sport';
  $handler->display->display_options['filters']['field_gozulla_sport_tid']['field'] = 'field_gozulla_sport_tid';
  $handler->display->display_options['filters']['field_gozulla_sport_tid']['value'] = array(
    14 => '14',
    15 => '15',
    13 => '13',
    20 => '20',
    18 => '18',
    19 => '19',
    12 => '12',
  );
  $handler->display->display_options['filters']['field_gozulla_sport_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_gozulla_sport_tid']['vocabulary'] = 'focus_sport';

  /* Display: surf */
  $handler = $view->new_display('page', 'surf', 'populate_surf');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'populate surf';
  $handler->display->display_options['display_description'] = 'gozulla surf directory';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gozullalocation' => 'gozullalocation',
  );
  /* Filter criterion: Proximity: Great-circle */
  $handler->display->display_options['filters']['circle']['id'] = 'circle';
  $handler->display->display_options['filters']['circle']['table'] = 'openlayers_proximity';
  $handler->display->display_options['filters']['circle']['field'] = 'circle';
  $handler->display->display_options['filters']['circle']['value']['value'] = '50';
  $handler->display->display_options['filters']['circle']['value']['location'] = 'Newport, OR';
  $handler->display->display_options['filters']['circle']['value']['node'] = '32745';
  $handler->display->display_options['filters']['circle']['exposed'] = TRUE;
  $handler->display->display_options['filters']['circle']['expose']['operator_id'] = 'circle_op';
  $handler->display->display_options['filters']['circle']['expose']['label'] = 'Great-circle';
  $handler->display->display_options['filters']['circle']['expose']['operator'] = 'circle_op';
  $handler->display->display_options['filters']['circle']['expose']['identifier'] = 'circle';
  $handler->display->display_options['filters']['circle']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['circle']['expose']['use_unit'] = 0;
  $handler->display->display_options['filters']['circle']['expose']['use_location'] = 0;
  $handler->display->display_options['filters']['circle']['expose']['use_node'] = 0;
  /* Filter criterion: Content: gozulla sport (field_gozulla_sport) */
  $handler->display->display_options['filters']['field_gozulla_sport_tid']['id'] = 'field_gozulla_sport_tid';
  $handler->display->display_options['filters']['field_gozulla_sport_tid']['table'] = 'field_data_field_gozulla_sport';
  $handler->display->display_options['filters']['field_gozulla_sport_tid']['field'] = 'field_gozulla_sport_tid';
  $handler->display->display_options['filters']['field_gozulla_sport_tid']['value'] = array(
    12 => '12',
  );
  $handler->display->display_options['filters']['field_gozulla_sport_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_gozulla_sport_tid']['vocabulary'] = 'focus_sport';
  $handler->display->display_options['path'] = 'populate/surf';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'surf';
  $handler->display->display_options['menu']['description'] = 'find surf shops near you';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-populate-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: skate */
  $handler = $view->new_display('page', 'skate', 'populate_skate');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'populate skate';
  $handler->display->display_options['display_description'] = 'gozulla skate directory';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gozullalocation' => 'gozullalocation',
  );
  /* Filter criterion: Proximity: Great-circle */
  $handler->display->display_options['filters']['circle']['id'] = 'circle';
  $handler->display->display_options['filters']['circle']['table'] = 'openlayers_proximity';
  $handler->display->display_options['filters']['circle']['field'] = 'circle';
  $handler->display->display_options['filters']['circle']['value']['value'] = '50';
  $handler->display->display_options['filters']['circle']['value']['location'] = 'Newport, OR';
  $handler->display->display_options['filters']['circle']['value']['node'] = '32756';
  $handler->display->display_options['filters']['circle']['exposed'] = TRUE;
  $handler->display->display_options['filters']['circle']['expose']['operator_id'] = 'circle_op';
  $handler->display->display_options['filters']['circle']['expose']['operator'] = 'circle_op';
  $handler->display->display_options['filters']['circle']['expose']['identifier'] = 'circle';
  $handler->display->display_options['filters']['circle']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['circle']['expose']['use_unit'] = 0;
  $handler->display->display_options['filters']['circle']['expose']['use_location'] = 1;
  $handler->display->display_options['filters']['circle']['expose']['use_node'] = 0;
  /* Filter criterion: Content: Sports (field_sport_type) */
  $handler->display->display_options['filters']['field_sport_type_tid']['id'] = 'field_sport_type_tid';
  $handler->display->display_options['filters']['field_sport_type_tid']['table'] = 'field_data_field_sport_type';
  $handler->display->display_options['filters']['field_sport_type_tid']['field'] = 'field_sport_type_tid';
  $handler->display->display_options['filters']['field_sport_type_tid']['value'] = array(
    18 => '18',
  );
  $handler->display->display_options['filters']['field_sport_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_sport_type_tid']['vocabulary'] = 'focus_sport';
  $handler->display->display_options['path'] = 'populate/skate';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'skate';
  $handler->display->display_options['menu']['description'] = 'find skate shops near you';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-populate-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: snow */
  $handler = $view->new_display('page', 'snow', 'populate_snow');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'populate ride';
  $handler->display->display_options['display_description'] = 'gozulla snow directory';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'populate/snow';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'snow';
  $handler->display->display_options['menu']['description'] = 'find snow shops near you';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-populate-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: bike */
  $handler = $view->new_display('page', 'bike', 'populate_bike');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'populate bike';
  $handler->display->display_options['display_description'] = 'gozulla bike directory';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gozullalocation' => 'gozullalocation',
  );
  /* Filter criterion: Proximity: Great-circle */
  $handler->display->display_options['filters']['circle']['id'] = 'circle';
  $handler->display->display_options['filters']['circle']['table'] = 'openlayers_proximity';
  $handler->display->display_options['filters']['circle']['field'] = 'circle';
  $handler->display->display_options['filters']['circle']['value']['value'] = '20';
  $handler->display->display_options['filters']['circle']['value']['location'] = 'Newport, OR';
  $handler->display->display_options['filters']['circle']['value']['node'] = '1630';
  $handler->display->display_options['filters']['circle']['exposed'] = TRUE;
  $handler->display->display_options['filters']['circle']['expose']['operator_id'] = 'circle_op';
  $handler->display->display_options['filters']['circle']['expose']['operator'] = 'circle_op';
  $handler->display->display_options['filters']['circle']['expose']['identifier'] = 'circle';
  $handler->display->display_options['filters']['circle']['expose']['use_unit'] = 0;
  $handler->display->display_options['filters']['circle']['expose']['use_location'] = 1;
  $handler->display->display_options['filters']['circle']['expose']['use_node'] = 0;
  /* Filter criterion: Content: Sports (field_sport_type) */
  $handler->display->display_options['filters']['field_sport_type_tid']['id'] = 'field_sport_type_tid';
  $handler->display->display_options['filters']['field_sport_type_tid']['table'] = 'field_data_field_sport_type';
  $handler->display->display_options['filters']['field_sport_type_tid']['field'] = 'field_sport_type_tid';
  $handler->display->display_options['filters']['field_sport_type_tid']['value'] = array(
    14 => '14',
  );
  $handler->display->display_options['filters']['field_sport_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_sport_type_tid']['vocabulary'] = 'focus_sport';
  $handler->display->display_options['path'] = 'populate/bike';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'bike';
  $handler->display->display_options['menu']['description'] = 'find bike shops near you';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-populate-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: climb */
  $handler = $view->new_display('page', 'climb', 'populate_climb');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'populate climb';
  $handler->display->display_options['display_description'] = 'gozulla climb directory';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gozullalocation' => 'gozullalocation',
  );
  /* Filter criterion: Proximity: Great-circle */
  $handler->display->display_options['filters']['circle']['id'] = 'circle';
  $handler->display->display_options['filters']['circle']['table'] = 'openlayers_proximity';
  $handler->display->display_options['filters']['circle']['field'] = 'circle';
  $handler->display->display_options['filters']['circle']['value']['value'] = '50';
  $handler->display->display_options['filters']['circle']['value']['location'] = 'Newport, OR';
  $handler->display->display_options['filters']['circle']['value']['node'] = '32756';
  $handler->display->display_options['filters']['circle']['exposed'] = TRUE;
  $handler->display->display_options['filters']['circle']['expose']['operator_id'] = 'circle_op';
  $handler->display->display_options['filters']['circle']['expose']['operator'] = 'circle_op';
  $handler->display->display_options['filters']['circle']['expose']['identifier'] = 'circle';
  $handler->display->display_options['filters']['circle']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['circle']['expose']['use_unit'] = 0;
  $handler->display->display_options['filters']['circle']['expose']['use_location'] = 1;
  $handler->display->display_options['filters']['circle']['expose']['use_node'] = 0;
  /* Filter criterion: Content: Sports (field_sport_type) */
  $handler->display->display_options['filters']['field_sport_type_tid']['id'] = 'field_sport_type_tid';
  $handler->display->display_options['filters']['field_sport_type_tid']['table'] = 'field_data_field_sport_type';
  $handler->display->display_options['filters']['field_sport_type_tid']['field'] = 'field_sport_type_tid';
  $handler->display->display_options['filters']['field_sport_type_tid']['value'] = array(
    13 => '13',
  );
  $handler->display->display_options['filters']['field_sport_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_sport_type_tid']['vocabulary'] = 'focus_sport';
  $handler->display->display_options['path'] = 'populate/climb';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'climb';
  $handler->display->display_options['menu']['description'] = 'find climb shops near you';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-populate-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: boat */
  $handler = $view->new_display('page', 'boat', 'populate_boat');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'populate boat';
  $handler->display->display_options['display_description'] = 'gozulla boat directory';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gozullalocation' => 'gozullalocation',
  );
  /* Filter criterion: Proximity: Great-circle */
  $handler->display->display_options['filters']['circle']['id'] = 'circle';
  $handler->display->display_options['filters']['circle']['table'] = 'openlayers_proximity';
  $handler->display->display_options['filters']['circle']['field'] = 'circle';
  $handler->display->display_options['filters']['circle']['value']['value'] = '50';
  $handler->display->display_options['filters']['circle']['value']['location'] = 'Newport, OR';
  $handler->display->display_options['filters']['circle']['value']['node'] = '32756';
  $handler->display->display_options['filters']['circle']['exposed'] = TRUE;
  $handler->display->display_options['filters']['circle']['expose']['operator_id'] = 'circle_op';
  $handler->display->display_options['filters']['circle']['expose']['operator'] = 'circle_op';
  $handler->display->display_options['filters']['circle']['expose']['identifier'] = 'circle';
  $handler->display->display_options['filters']['circle']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['circle']['expose']['use_unit'] = 0;
  $handler->display->display_options['filters']['circle']['expose']['use_location'] = 1;
  $handler->display->display_options['filters']['circle']['expose']['use_node'] = 0;
  /* Filter criterion: Content: Sports (field_sport_type) */
  $handler->display->display_options['filters']['field_sport_type_tid']['id'] = 'field_sport_type_tid';
  $handler->display->display_options['filters']['field_sport_type_tid']['table'] = 'field_data_field_sport_type';
  $handler->display->display_options['filters']['field_sport_type_tid']['field'] = 'field_sport_type_tid';
  $handler->display->display_options['filters']['field_sport_type_tid']['value'] = array(
    15 => '15',
  );
  $handler->display->display_options['filters']['field_sport_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_sport_type_tid']['vocabulary'] = 'focus_sport';
  $handler->display->display_options['path'] = 'populate/boat';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'boat';
  $handler->display->display_options['menu']['description'] = 'find boat shops near you';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-populate-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: golf */
  $handler = $view->new_display('page', 'golf', 'populate_golf');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'populate golf';
  $handler->display->display_options['display_description'] = 'gozulla golf directory';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gozullalocation' => 'gozullalocation',
  );
  /* Filter criterion: Proximity: Great-circle */
  $handler->display->display_options['filters']['circle']['id'] = 'circle';
  $handler->display->display_options['filters']['circle']['table'] = 'openlayers_proximity';
  $handler->display->display_options['filters']['circle']['field'] = 'circle';
  $handler->display->display_options['filters']['circle']['value']['value'] = '50';
  $handler->display->display_options['filters']['circle']['value']['location'] = 'Newport, OR';
  $handler->display->display_options['filters']['circle']['value']['node'] = '32756';
  $handler->display->display_options['filters']['circle']['exposed'] = TRUE;
  $handler->display->display_options['filters']['circle']['expose']['operator_id'] = 'circle_op';
  $handler->display->display_options['filters']['circle']['expose']['operator'] = 'circle_op';
  $handler->display->display_options['filters']['circle']['expose']['identifier'] = 'circle';
  $handler->display->display_options['filters']['circle']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    4 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['circle']['expose']['use_unit'] = 0;
  $handler->display->display_options['filters']['circle']['expose']['use_location'] = 1;
  $handler->display->display_options['filters']['circle']['expose']['use_node'] = 0;
  /* Filter criterion: Content: Sports (field_sport_type) */
  $handler->display->display_options['filters']['field_sport_type_tid']['id'] = 'field_sport_type_tid';
  $handler->display->display_options['filters']['field_sport_type_tid']['table'] = 'field_data_field_sport_type';
  $handler->display->display_options['filters']['field_sport_type_tid']['field'] = 'field_sport_type_tid';
  $handler->display->display_options['filters']['field_sport_type_tid']['value'] = array(
    20 => '20',
  );
  $handler->display->display_options['filters']['field_sport_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_sport_type_tid']['vocabulary'] = 'focus_sport';
  $handler->display->display_options['path'] = 'populate/golf';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'golf';
  $handler->display->display_options['menu']['description'] = 'find golf shops near you';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-populate-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['populatedatabase'] = array(
    t('Master'),
    t('Populate'),
    t('more'),
    t('Apply'),
    t('Find Me'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Displaying @start - @end of @total'),
    t('[ edit ]'),
    t('.'),
    t(','),
    t('All'),
    t('surf'),
    t('populate surf'),
    t('gozulla surf directory'),
    t('Great-circle'),
    t('skate'),
    t('populate skate'),
    t('gozulla skate directory'),
    t('snow'),
    t('populate ride'),
    t('gozulla snow directory'),
    t('bike'),
    t('populate bike'),
    t('gozulla bike directory'),
    t('climb'),
    t('populate climb'),
    t('gozulla climb directory'),
    t('boat'),
    t('populate boat'),
    t('gozulla boat directory'),
    t('golf'),
    t('populate golf'),
    t('gozulla golf directory'),
  );
  $export['populatedatabase'] = $view;

  return $export;
}

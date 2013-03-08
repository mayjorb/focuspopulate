<?php

/**
 * @file
 * focuspopulate_shops.inc
 *
 * builds factual shop directories
*/

//try {

// factual driver files
require_once('factual-php-driver/Factual.php');

// googlePlaces class 
require_once('googlePlaces/googlePlaces.php');


$apiKey       = 'AIzaSyBYeTRKL_nASXiS8VYKILULQU3mq7TUUMk';
$googlePlaces = new googlePlaces($apiKey);

// set api key for oauth
$factual_key = variable_get('gozulla_directory_factual_key',0);
$factual_secret = variable_get('gozulla_directory_factual_secret',0);
$factual = new Factual($factual_key,$factual_secret); //2-legged OAUTH


function focuspopulate_miles_to_meters($miles) {
  $meters = round($miles * 1609.344);
  return $meters;
}

function focuspopulate_meters_to_miles($meters) {
  $miles = $meters * 0.000621371192 * 10 / 10;
  $miles = round($miles, 1);
  return $miles;
}

if (isset($_GET['circle']['location']) && $_GET['circle']['location']) {
  $thislocation = $_GET['circle']['location'];
  $geolookup = $factual->geocode($thislocation);
}
else {
  $geolookup = $factual->geocode("Bend, OR");
}
   
$latitude   = $geolookup['latitude']; 
$longitude = $geolookup['longitude'];

$googlePlaces->setLocation($latitude . ',' . $longitude);

// set circle radius
if (isset($_GET['circle']['value']) && is_numeric($_GET['circle']['value'])) {
  $radius = $_GET['circle']['value'];
}
else {
  $radius =  50;
}
// $radius =  50;
//$circle_radius = focuspopulate_miles_to_meters($radius);

$limit = 5;
$offset = 0;


$shops = '';

switch ($sport) {

  case 'bike':
    $tid = 14; // term ID from focus_sport taxonomy
    //start building search
    $googlePlaces->setQuery('bicycle,bike shop,bike');
    $googlePlaces->setTypes('store'); //$circle_radius = focuspopulate_miles_to_meters($radius);
    $googlePlaces->setRadius($radius);

    $gresults = $googlePlaces->textSearch();
    
    break;

  case 'boat':
    $tid = 15; // term ID from focus_sport taxonomy
    //start building search
    $googlePlaces->setQuery('canoe,kayak,boat,paddle');
    $googlePlaces->setTypes('store'); //$circle_radius = focuspopulate_miles_to_meters($radius);
    $googlePlaces->setRadius($radius);

    $gresults = $googlePlaces->textSearch();
    break;  

  case 'climb':
    $tid = 13; // term ID from focus_sport taxonomy
    //start building search
    $googlePlaces->setQuery('climbing,mountain climbing,climbing wall');
    $googlePlaces->setTypes('store'); //$circle_radius = focuspopulate_miles_to_meters($radius);
    $googlePlaces->setRadius($radius);

    $gresults = $googlePlaces->textSearch();
    
    break;
  
  case 'golf':
    $tid = 20; // term ID from focus_sport taxonomy
    //start building search
    $googlePlaces->setQuery('golf shop');
    $googlePlaces->setTypes('store'); //$circle_radius = focuspopulate_miles_to_meters($radius);
    $googlePlaces->setRadius($radius);

    $gresults = $googlePlaces->textSearch();
    
    break; 

  case 'skate':
    $tid = 18; // term ID from focus_sport taxonomy
    //start building search
    $googlePlaces->setQuery('skateboard,skate shop');
    $googlePlaces->setTypes('store'); //$circle_radius = focuspopulate_miles_to_meters($radius);
    $googlePlaces->setRadius($radius);

    $gresults = $googlePlaces->textSearch();
    
    break;

  case 'snow':
    $tid = 19; // term ID from focus_sport taxonomy
    //start building search
    $googlePlaces->setQuery('snowboard,ski');
    $googlePlaces->setTypes('store'); //$circle_radius = focuspopulate_miles_to_meters($radius);
    $googlePlaces->setRadius($radius);

    $gresults = $googlePlaces->textSearch();
    
    break; 
  
  case 'surf':
    $tid = 12; // term ID from focus_sport taxonomy

    //start building search
    $googlePlaces->setQuery('surfshop, surfboards');
    $googlePlaces->setTypes('store'); //$circle_radius = focuspopulate_miles_to_meters($radius);
    $googlePlaces->setRadius($radius);

    $gresults = $googlePlaces->textSearch();

    break;
}

if ($gresults['status'] == 'OK') {

  // Get an associative array of places_id's.
  $existingnodes = db_query("SELECT field_places_id_value AS places_id  FROM {field_data_field_places_id}")->fetchCol();

  foreach ($gresults['results'] as $value) { 

    if (!in_array($value['id'],$existingnodes)) { // don't add node if already in db

    $thisaddress = explode(',', $value['formatted_address']);

    global $user;

    $node = new stdClass(); // create new node object
    $node->type = 'gozullalocation';
    $node->language = LANGUAGE_NONE;
    $node->uid = $user->uid; 
    node_object_prepare($node);
    $node->title = $value['name'];
    $node->field_address['und'][0]['thoroughfare'] = $thisaddress[0]; // street
    $node->field_address['und'][0]['locality'] = $thisaddress[1]; // city
    $node->field_address['und'][0]['administrative_area'] = $thisaddress[2]; // state
    //$node->field_address['und'][0]['postal_code'] = $thisaddress[3]; // zipcode
    $node->field_address['und'][0]['country'] = 'US';
    $node->field_geofield['und'][0]['lat'] = $value['geometry']['location']['lat'];
    $node->field_geofield['und'][0]['lon'] = $value['geometry']['location']['lng'];
    //$node->field_phone['und'][0]['value'] = $value['tel'];
    //$node->field_website['und'][0]['url'] = $value['website'];
    $node->field_sport_type['und'][0]['tid'] = $tid;
    $node->field_geofield['und'][0]['source'] = $source;
    $node->field_places_id['und'][0]['value'] = $value['id'];
    $node->field_unique_id['und'][0]['value'] = $value['reference'];
    $node->status = 1;
    $node->revision = 1;
    $node->log = 'This node was created via focuspopulate module at ' . date('c');

    node_save($node);

    // drupal_set_message(t('node ' . $value['name'] . ' created'));
    $shops .='<div>' . $value['name'] . ' at ' . $thisaddress[0] . ' ' . $thisaddress[1] . ', ' . $thisaddress[2] . ' created</div>'; // display newly created shops

    // get details then update node
    $googlePlaces->setReference($value['reference']);
    $results = $googlePlaces->Details();

    // entity_id (nid) from new node
    $query = "SELECT entity_id AS nid FROM {field_data_field_unique_id} WHERE field_unique_id_value = '" . $value['reference'] . "'";
    
    $result = db_query($query)->fetchField();
      
    $query = new EntityFieldQuery();

    $query
      ->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'gozullalocation')
      ->propertyCondition('nid', $result)
      ->range(0, 1);
       
    $result = $query->execute();

    $nid = array_keys($result['node']); // sets the nid to the current value in loop
        
    $nid = $nid[0]; // Drupal needs this to be a string

    $node = node_load($nid); // load the node

    node_object_prepare($node);

    // set tne new values
    $node->type = 'gozullalocation';
    $node->field_phone['und'][0]['value'] = $results['result']['formatted_phone_number'];
    $node->field_website['und'][0]['url'] = $results['result']['website'];
    $node->field_address['und'][0]['administrative_area'] = $results['result']['address_fixed']['address_state']; // state
    $node->field_address['und'][0]['postal_code'] = $results['result']['address_fixed']['address_postal_code']; // zipcode

    $node->revision = 1;
    $node->log = 'This node was updated via focuspopulate module at ' . date('c');

    if ($node = node_submit($node)) {
      node_save($node);
       // drupal_set_message(t('node ' . $value['name'] . ' updated'));
    }
    else {
      drupal_set_message(t('node ' . $value['name'] . ' update failed'));
    }

  }

  else { // add tid for existing nodes

    // entity_id (nid) from new node
    $query = "SELECT entity_id AS nid  FROM {field_data_field_places_id} WHERE field_places_id_value = '" . $value['id'] . "'";
    
    $result = db_query($query)->fetchField();

    //dpm($result,'nid for sport update');
      
    $query = new EntityFieldQuery();

    $query
      ->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'gozullalocation')
      ->propertyCondition('nid', $result)
      ->range(0, 1);
       
    $result = $query->execute();

    $nid = array_keys($result['node']); // sets the nid to the current value in loop
        
    $nid = $nid[0]; // Drupal needs this to be a string

    $node = node_load($nid); // load the node

    // dpm($node,'node object');

    node_object_prepare($node);

    // set tne new values
    $node->type = 'gozullalocation';

    $node->field_sport_type['und'][] = array('tid' => $tid);

    $node->revision = 1;
    $node->log = 'Sport updated via focuspopulate module at ' . date('c');

    $thisshop = $value['name'];

    if ($node = node_submit($node)) {
      node_save($node);
      $shops .='<div>' . $sport . ' category added/updated to ' . $thisshop . '</div>'; // display newly created shops
       //drupal_set_message(t('Sport: ' . $sport . ' added to ' . $thisshop));
    }
    // else {
    //   drupal_set_message(t('Sport: ' . $sport . ' was not added to ' . $thisshop));
    // }


  }

  // dpm($existingnodes,'existing nodes');
  //} // $foreach

 } // $gresults['status']



}
else {
  print 'status = ' . $gresults['status'];

  $sport = '';
  $shops .= '<div class="places-row last"><h3 class="places-shop">no ' . $sport . ' shops found</h3><div class="places-detail">Try increasing the miles and/or changing the location.</div></div>';
}


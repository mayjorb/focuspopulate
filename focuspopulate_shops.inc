<?php

/**
 * @file
 * focuspopulate_shops.inc
 *
 * builds factual shop directories
*/


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

// if (isset($_SESSION['ip_geoloc']['location']['locality']) && isset($_SESSION['ip_geoloc']['location']['administrative_area_level_1'])) {
//   $city_state = $_SESSION['ip_geoloc']['location']['locality'] . ', ' . $_SESSION['ip_geoloc']['location']['administrative_area_level_1'];
// }
// else {
//   $city_state = t('Newport, OR');
// }

if (isset($_SESSION['ip_geoloc']['location']['locality']) && isset($_SESSION['ip_geoloc']['location']['administrative_area_level_1'])) {
    $city_state = $_SESSION['ip_geoloc']['location']['locality'] . ', ' . $_SESSION['ip_geoloc']['location']['administrative_area_level_1'];
  }
  else {
    $city_state = t('Newport, OR');
  }

  // set circle radius
  if (isset($_GET['circle']['value']) && is_numeric($_GET['circle']['value']) && $_GET['circle']['value'] <= 31) {
    $radius = $_GET['circle']['value'];
  }
  else {
    $radius =  31;
  }



if (isset($_SESSION['ip_geoloc']['location']['latitude']) && isset($_SESSION['ip_geoloc']['location']['longitude'])) {
  $user_lat = $_SESSION['ip_geoloc']['location']['latitude'];
  $user_lon = $_SESSION['ip_geoloc']['location']['longitude'];
}
else {
  $user_lat = '44.6367836'; // newport, oregon
  $user_lon = '-124.0534505';
}


if (isset($_GET['circle']['location']) && $_GET['circle']['location']) {

  // geocode (convert an address to longitude and latitude) if submitted in form
  $location = $_GET['circle']['location'];
  
  $geolookup = $factual->geocode($location);

  // if latitude and longitude are found use these values
  if (isset($geolookup['latitude']) && $geolookup['latitude'] && isset($geolookup['longitude']) && $geolookup['longitude']) {
    $user_lat = $geolookup['latitude'];
    $user_lon = $geolookup['longitude'];
  }
  
}

// // set circle radius
if (isset($_GET['circle']['value']) && is_numeric($_GET['circle']['value']) && $_GET['circle']['value'] <= 31) {
  $radius = $_GET['circle']['value'];
}
else {
  $radius =  31;
}

$googlePlaces->setLocation($user_lat . ',' . $user_lon);

$shops = '';

$radiusmeters = focuspopulate_miles_to_meters($radius);

if ($radiusmeters > 50000) {
  $radiusmeters = 50000;
}

switch ($sport) {

  case 'bike':
    $tid = 14; // term ID from focus_sport taxonomy
    //start building search
    $googlePlaces->setQuery('bicycle,bike shop');
    $googlePlaces->setTypes('store'); //$circle_radius = focuspopulate_miles_to_meters($radius);
    $googlePlaces->setRadius($radiusmeters);

    $gresults = $googlePlaces->textSearch();
    
    break;

  case 'boat':
    $tid = 15; // term ID from focus_sport taxonomy
    //start building search
    $googlePlaces->setQuery('canoe,kayak,boat,paddle');
    $googlePlaces->setTypes('store'); //$circle_radius = focuspopulate_miles_to_meters($radius);
    $googlePlaces->setRadius($radiusmeters);

    $gresults = $googlePlaces->textSearch();
    break;  

  case 'climb':
    $tid = 13; // term ID from focus_sport taxonomy
    //start building search
    $googlePlaces->setQuery('climbing,climbing gym');
    $googlePlaces->setTypes('store'); //$circle_radius = focuspopulate_miles_to_meters($radius);
    $googlePlaces->setRadius($radiusmeters);

    $gresults = $googlePlaces->textSearch();
    
    break;
  
  case 'golf':
    $tid = 20; // term ID from focus_sport taxonomy
    //start building search
    $googlePlaces->setQuery('golf shop');
    $googlePlaces->setTypes('store'); //$circle_radius = focuspopulate_miles_to_meters($radius);
    $googlePlaces->setRadius($radiusmeters);

    $gresults = $googlePlaces->textSearch();
    
    break; 

  case 'skate':
    $tid = 18; // term ID from focus_sport taxonomy
    //start building search
    $googlePlaces->setQuery('skateboard, skate shop');
    $googlePlaces->setTypes('store'); //$circle_radius = focuspopulate_miles_to_meters($radius);
    $googlePlaces->setRadius($radiusmeters);

    $gresults = $googlePlaces->textSearch();
    
    break;

  case 'snow':
    $tid = 19; // term ID from focus_sport taxonomy
    //start building search
    $googlePlaces->setQuery('snowboard,ski');
    $googlePlaces->setTypes('store'); //$circle_radius = focuspopulate_miles_to_meters($radius);
    $googlePlaces->setRadius($radiusmeters);

    $gresults = $googlePlaces->textSearch();
    
    break; 
  
  case 'surf':
    $tid = 12; // term ID from focus_sport taxonomy

    //start building search
    $googlePlaces->setQuery('surfshop, surfboards');
    $googlePlaces->setTypes('store'); //$circle_radius = focuspopulate_miles_to_meters($radius);
    $googlePlaces->setRadius($radiusmeters);

    $gresults = $googlePlaces->textSearch();

    break;
}
  drupal_set_message('Status of googlePlaces search: ' . $gresults['status']);
  //dpm($gresults['results'],'Results of googlePlaces search');

if ($gresults['status'] == 'OK') {

  $total = count($gresults['results']);
  drupal_set_message($total . ' shops found');

  // Get an associative array of places_id's.
  $existingnodes = db_query("SELECT field_places_id_value AS places_id  FROM {field_data_field_places_id}")->fetchCol();
  // $focus_total = count($existingnodes);
  // drupal_set_message($focus_total . ' shops found in Focus Database');

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

      drupal_set_message(t($value['name'] . ' at ' . $thisaddress[0] . ' ' . $thisaddress[1] . ', ' . $thisaddress[2] . ' created'));
      drupal_set_message(t('Click the "go" button to view newly added shops.'), 'warning', $repeat = FALSE);

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
        $update = TRUE;
      }
      else {
        drupal_set_message(t('node ' . $value['name'] . ' update failed'));
      }

    }

    else { // add tid for existing nodes

      // entity_id (nid) from new node
      $query = "SELECT entity_id AS nid  FROM {field_data_field_places_id} WHERE field_places_id_value = '" . $value['id'] . "'";

      if (count($query)) { // don't try to update if nothing to update
        
        $update = FALSE;
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

        $thisshop = $value['name'];

        // dpm($node->field_sport_type['und'][] = array('tid' => $tid), 'does this return tids');
        $existingtids = $node->field_sport_type['und'][] = array('tid' => $tid);
        //dpm($tid, 'tid value');

        //dpm($existingtids, 'existingtids');
        if (!in_array($tid,$existingtids)) { // don't add sport if already in db
      
          node_object_prepare($node);

          // set the new values
          $node->type = 'gozullalocation';
          $node->field_sport_type['und'][] = array('tid' => $tid);
          $node->revision = 1;
          $node->log = 'Sport updated via focuspopulate module at ' . date('c');

          if ($node = node_submit($node)) {
          //node_save($node);
            drupal_set_message(t($sport . ' category added to ' . $thisshop), 'warning');
          }

        }  //!in_array($tid,$existingtids

      } //count($query
    
    } // foreach

 
  } //else

}// $gresults['status']

  if (!$update) {
    drupal_set_message(t('No new shops were added'), 'warning');
  }



// else {

//   drupal_set_message(t('googlePlaces status',$gresults['status']), 'warning');

// }


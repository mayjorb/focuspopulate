<?php

require_once('../krumo/class.krumo.php');
require_once('googlePlaces.php');

$apiKey       = 'AIzaSyBYeTRKL_nASXiS8VYKILULQU3mq7TUUMk';
$googlePlaces = new googlePlaces($apiKey);

// Set the longitude and the latitude of the location you want to search the surronds of
$latitude   = '49.273677';
$longitude = '-123.114420';
$googlePlaces->setLocation($latitude . ',' . $longitude);


$googlePlaces->setQuery('surfshop');
$googlePlaces->setRadius(5000);
$results = $googlePlaces->textSearch();




?>


<?php 
krumo($results);
?>


hey now
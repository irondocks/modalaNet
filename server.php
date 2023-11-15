<?php

// server.php

// Function to generate a random content for the window
function generateContent() {
  $content = '';
  $length = rand(5, 10);
  $characters = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';
  $charactersLength = strlen($characters);
  for ($i = 0; $i < $length; $i++) {
    $content .= $characters[rand(0, $charactersLength - 1)];
  }
  return $content;
}

// Function to generate the window server data
function generateData() {
  $data = [];
  $numWindows = rand(3, 6);
  for ($i = 0; $i < $numWindows; $i++) {
    $window = [
      'id' => $i + 1,
      'content' => generateContent()
    ];
    array_push($data, $window);
  }
  return $data;
}

// Generate the data and output as JSON
$data = generateData();
header('Content-Type: application/json');
echo json_encode($data);

?>

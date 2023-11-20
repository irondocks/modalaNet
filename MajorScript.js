// script.js

// Function to fetch data from the server
function fetchData(url) {
  return fetch(url)
    .then(response => response.json())
    .catch(error => console.log(error));
}

// Function to update the DOM with the fetched data
function updateDOM(data) {
  const windowServer = document.getElementById('windowServer');
  windowServer.innerHTML = '';

  data.forEach(element => {
    const div = document.createElement('div');
    div.className = 'window';
    div.innerHTML = element.content;
    windowServer.appendChild(div);
  });
}

// Function to fetch and update the DOM
function fetchAndUpdateDOM() {
  fetchData('server.php')
    .then(data => updateDOM(data))
    .catch(error => console.log(error));
}

// Function to initialize the window server
function initWindowServer() {
  fetchAndUpdateDOM();
  setInterval(fetchAndUpdateDOM, 5000);
}

// Call the initialization function
initWindowServer();

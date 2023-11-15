// dom.js

// Function to create a DOM-compliant element
function createElement(tagName, attributes, content) {
  const element = document.createElement(tagName);
  for (const key in attributes) {
    element.setAttribute(key, attributes[key]);
  }
  if (content) {
    element.innerHTML = content;
  }
  return element;
}

// Function to update the DOM with the fetched data
function updateDOM(data) {
  const windowServer = document.getElementById('windowServer');
  windowServer.innerHTML = '';

  data.forEach(element => {
    const div = createElement('div', { class: 'window' }, element.content);
    windowServer.appendChild(div);
  });
}

// Function to fetch and update the DOM
function fetchAndUpdateDOM() {
  fetchData('server.php')
    .then(data => updateDOM(data))
    .catch(error => console.log(error));
}

// Call the initialization function
initWindowServer();

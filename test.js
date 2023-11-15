// test.js

// Import the necessary functions and modules
const { createElement, updateDOM, fetchAndUpdateDOM } = require('./dom.js');
const { fetchData } = require('./fetch.js');

// Test the createElement function
const element = createElement('div', { class: 'test' }, 'Hello, world!');
console.log(element);

// Test the updateDOM function
const data = [
  { content: 'Content 1' },
  { content: 'Content 2' },
  { content: 'Content 3' }
];
updateDOM(data);

// Test the fetchAndUpdateDOM function
fetchAndUpdateDOM();

// Test the fetchData function
fetchData('server.php')
  .then(data => console.log(data))
  .catch(error => console.log(error));
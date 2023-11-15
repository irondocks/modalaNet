// json.js

// Function to write JSON data to a file
function writeJSON(data, filename) {
  const jsonString = JSON.stringify(data);
  const blob = new Blob([jsonString], { type: 'application/json' });
  const url = URL.createObjectURL(blob);

  const a = document.createElement('a');
  a.href = url;
  a.download = filename;
  a.click();

  URL.revokeObjectURL(url);
}

// Function to read JSON data from a file
function readJSON(file) {
  return new Promise((resolve, reject) => {
    const reader = new FileReader();

    reader.onload = function (event) {
      try {
        const data = JSON.parse(event.target.result);
        resolve(data);
      } catch (error) {
        reject(error);
      }
    };

    reader.onerror = function (event) {
      reject(event.target.error);
    };

    reader.readAsText(file);
  });
}

// Function to fetch data from the server
function fetchData(url) {
  return new Promise((resolve, reject) => {
    const xhr = new XMLHttpRequest();
    xhr.open('GET', url);
    xhr.onload = function () {
      if (xhr.status === 200) {
        try {
          const data = JSON.parse(xhr.responseText);
          resolve(data);
        } catch (error) {
          reject(error);
        }
      } else {
        reject(new Error('Failed to fetch data'));
      }
    };
    xhr.onerror = function () {
      reject(new Error('Failed to fetch data'));
    };
    xhr.send();
  });
}

// Function to send data to the server
function sendData(url, data) {
  return new Promise((resolve, reject) => {
    const xhr = new XMLHttpRequest();
    xhr.open('POST', url);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.onload = function () {
      if (xhr.status === 200) {
        resolve();
      } else {
        reject(new Error('Failed to send data'));
      }
    };
    xhr.onerror = function () {
      reject(new Error('Failed to send data'));
    };
    xhr.send(JSON.stringify(data));
  });
}

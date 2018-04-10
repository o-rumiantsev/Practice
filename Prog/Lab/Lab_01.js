'use strict';

const fs = require('fs');

function csv() {};

csv.read = (file) => {
  const data = fs.readFileSync(file, 'utf8');
  const lines = data.split('\n');

  return lines;
}

csv.write = (filename, rawData) => {
  rawData.forEach(el => el.join());
  const data = rawData.join('\n');
  fs.writeFileSync(filename, data);
};

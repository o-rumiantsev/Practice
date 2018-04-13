'use strict';

const fs = require('fs');

function csv() {}

csv.read = (file) => {
  const data = fs.readFileSync(file, 'utf8');
  const lines = data.split('\n');

  return lines;
};

csv.write = (filename, rawData) => {
  rawData.forEach(el => el.join());
  const data = rawData.join('\n');
  fs.writeFileSync(filename, data);
};

const defineFellow = (data) => {
  const amount = data.shift();
  const fellowsAmount = Math.floor(amount * 0.4);
  const students = [];

  data.forEach(line => {
    const info = line.split(',');
    const surname = info.shift();
    const contract =  info.pop();
    const average = info.reduce((a, b) => +a + +b, 0) / info.length;

    if (contract === 'FALSE') {
      const student = [surname, average];
      students.push(student);
    }
  });

  students.sort((a, b) => (a[1] < b[1] ? 1 : -1));
  return students.slice(0, fellowsAmount);
};


const data = csv.read('./students.csv');
const fellows = defineFellow(data);
csv.write('./rating.csv', fellows);

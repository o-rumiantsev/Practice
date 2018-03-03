'use strict';

const { exec } = require('child_process');

exec('./rust/sudoku', (err, stdout, stderr) => {
  if (err) throw err;
  if (stderr) {
    console.error(stderr);
    return;
  }

  console.log(stdout);
})

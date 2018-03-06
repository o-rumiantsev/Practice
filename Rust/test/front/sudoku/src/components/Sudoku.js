import React, { Component } from 'react';
import { Table } from 'semantic-ui-react';
import injectSheet from 'react-jss';

import CellContainer from '../containers/CellContainer';


const styles = {
  table: {

  },
  rows: {

  },
  cells: {

  }
}

const intoCells = (row, classes) => {
  const cells = new Array(9).fill(0);
  return cells.map((cell, i) => (
    <Table.Cell key = {`${row}${i + 1}`} className = {classes.cells} >
      <CellContainer cellid = {`${row}${i + 1}`}/>
    </Table.Cell>
  ));
};

const formRows = (classes) => {
  const rows = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'];
  return rows.map((row, i) => (
    <Table.Row key = {i} className = {classes.rows}>
      {intoCells(row, classes)}
    </Table.Row>
  ));
}

class Sudoku extends Component {
  render() {
    const { classes } = this.props;
    return (
      <div>
        <center>
          <Table className = {classes.table} celled>
            <Table.Body>{formRows(classes)}</Table.Body>
          </Table>
        </center>
      </div>
    )
  }
}

export default injectSheet(styles)(Sudoku);

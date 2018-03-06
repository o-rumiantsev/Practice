import React, { Component } from 'react';
import injectSheet from 'react-jss';
import { connect } from 'react-redux';

import { addValue, deleteValue } from '../actions';

const styles = {
  cell: {
    height: '40px',
    width: '40px',
    fontSize: '40px',
    outline: 'none'
  }
}


const validateInput = (value) => {
  if (value === '') return value;
  const len = value.length;
  const parsed = parseInt(value[len - 1]);
  if (!parsed || parsed.length < len) return false;
  if (parsed < 1 || parsed > 9) return false;
  return value[len - 1];
}

const ids = [];

['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i']
  .forEach((row) => {
    for (let i = 1; i < 10; i++) ids.push(`${row}${i}`);
  });


class Cell extends Component {
  constructor(props) {
    super(props);
    this.state = { value: '' };
  }

  focusInput = () => this.textInput.focus();

  componentWillReceiveProps = (nextProps) => {
    if (nextProps.active) this.focusInput();
  }

  handleChange = (event) => {
    const value = validateInput(event.target.value);
    if (value) {
      this.setState({ value });
      this.props.updateValue(this.props.cellid, value);
    }
  }

  onKeyDown = (event) => {
    const key = event.key;
    const currId = ids.indexOf(this.props.cellid);
    switch (key) {
      case 'ArrowLeft':
        if (ids[currId - 1]) this.props.moveCursor(ids[currId - 1]);
        break;
      case 'ArrowRight': case 'Enter':
        if (ids[currId + 1]) this.props.moveCursor(ids[currId + 1]);
        break;
      case 'ArrowUp':
        if (ids[currId - 9]) this.props.moveCursor(ids[currId - 9]);
        break;
      case 'ArrowDown':
        if (ids[currId + 9]) this.props.moveCursor(ids[currId + 9]);
        break;
      case 'Backspace': case  'Delete':
        this.setState({ value: '' });
        deleteValue(this.cellid);
        break;
    }
  }

  render() {
    const { classes } = this.props;
    return (
      <input className = {classes.cell} type = "text"
        value = {this.state.value} onChange = {this.handleChange}
        onKeyDown = {this.onKeyDown}
        ref = {(input) => { this.textInput = input; }}/>
    )
  }
}

export default connect(
  state => state,
  (dispatch) => ({
    updateValue: (id, value) => dispatch(addValue(id, value)),
    deleteValue: (id) => dispatch(deleteValue(id))
  })
)(injectSheet(styles)(Cell));

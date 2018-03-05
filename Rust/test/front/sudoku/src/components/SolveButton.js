import React, { Component } from 'react';
import { Button } from 'semantic-ui-react';
import injectSheet from 'react-jss';

const styles = {
  button: {
    marginTop: '10px',
    border: 'none',
    borderRadius: '5px',
    height: '40px',
    width: '80px',
    color: 'Dark Grey',
    fontSize: '18px',
    fontFamily: 'Arial',
    outline: 'none',
    boxShadow: '0 8px 16px 0 rgba(0,0,0,0.2), 0 6px 16px 0 rgba(0,0,0,0.19)'
  },
}

class SolveButton extends Component {
  render() {
    const { classes } = this.props;
    return (
      <div>
        <center>
          <Button className = {classes.button}>Solve</Button>
        </center>
      </div>
    )
  }
}

export default injectSheet(styles)(SolveButton);

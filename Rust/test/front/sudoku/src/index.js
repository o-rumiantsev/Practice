import React from 'react';
import ReactDOM from 'react-dom';
import { Provider } from 'react-redux';
import { createStore } from 'redux';

import Sudoku from './components/Sudoku';
import SolveButton from './components/SolveButton';
import reducer from './reducers';

let store = createStore(reducer);

ReactDOM.render((
    <Provider store = {store}>
      <div>
        <Sudoku />
        <SolveButton />
      </div>
    </Provider>
  ),
  document.getElementById('root')
);

import { ADD_VALUE, DELETE_VALUE } from '../actions';

const initialState = [];

['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i']
  .forEach((row) => {
    for (let i = 1; i < 10; i++) initialState.push({
      id: `${row}${i}`,
      value: ''
    });
  });

let newState = null;

const modifyValue = (state = initialState, action) => {
  switch (action.type) {
    case ADD_VALUE:
      newState = state.find(cell => (cell.id === action.id));
      newState.value = action.value;
      return [...state];
    case DELETE_VALUE:
      newState = state.find(cell => (cell.id === action.id));
      newState.value = '';
      return [...state];
    default:
      return state;
  }
}

export default modifyValue;

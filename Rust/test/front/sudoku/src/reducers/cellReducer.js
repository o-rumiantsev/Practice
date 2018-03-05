import { CHANGE_CELL } from '../actions'
const initialState = [];

['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i']
  .forEach((row) => {
    for (let i = 1; i < 10; i++) initialState.push({
      id: `${row}${i}`,
      active: false
    });
  });

const changeCell = (state = initialState, action) => {
  switch (action.type) {
    case CHANGE_CELL:
      return state.map((cell) => (
        (cell.id === action.id) || cell.active ?
          { id: cell.id, active: !cell.active } : cell
      ));
    default:
      return state;
  }
}

export default changeCell;

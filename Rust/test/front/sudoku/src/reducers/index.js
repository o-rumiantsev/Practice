import { combineReducers } from 'redux';
import cellReducer from './cellReducer';
import modifyReducer from './modifyReducer';

const reducer = combineReducers({
  cellReducer,
  modifyReducer
});

export default reducer;

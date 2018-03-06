export const CHANGE_CELL = 'CHANGE_CELL';
export const ADD_VALUE = 'ADD_VALUE';
export const DELETE_VALUE = 'DELETE_VALUE';

export function changeCell(id) {
  return { type: CHANGE_CELL, id }
};

export function addValue(id, value) {
  return { type: ADD_VALUE, id, value }
};

export function deleteValue(id) {
  return { type: DELETE_VALUE, id }
};

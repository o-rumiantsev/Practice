import { connect } from 'react-redux';
import { changeCell } from '../actions';
import Cell from '../components/Cell';

const mapStateToProps = (state, ownProps) => {
  return {
    cellid: ownProps.cellid,
    active: state.cellReducer.id === ownProps.cellid
  }
}

const mapDispatchToProps = (dispatch) => ({
  moveCursor: id => dispatch(changeCell(id))
});

const CellContainer = connect(
  mapStateToProps,
  mapDispatchToProps
)(Cell);

export default CellContainer;

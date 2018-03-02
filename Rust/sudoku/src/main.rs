extern crate sudoku;

use sudoku::input;
use sudoku::points;

fn main() {
    let data = input::get();
    for d in &data {
        println!("{:?}", d);
    }

    let mut points = points::get(&data);
    points::sort(&mut points);

    for p in &points {
        println!("{:?}", p);
    }

    // let result = sudoku::solve(&data, &mut points);
}

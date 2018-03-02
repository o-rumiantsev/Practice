extern crate sudoku;

use sudoku::input;
use sudoku::points;
use sudoku::test;

fn main() {
    let data = input::get();

    let mut points = points::get(&data);
    points::sort(&mut points);

    let result = sudoku::solve(&data, &mut points, 0);

    for r in &result {
        println!("{:?}", r);
    }

    let valid = test::validate(&result);

    if valid {
        println!("Success!");
    } else {
        println!("Still not bad...");
    }
}

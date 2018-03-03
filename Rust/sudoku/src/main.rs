extern crate sudoku;

use sudoku::input;
use sudoku::points;
use sudoku::test;

fn main() {
    let data = input::get();
    let mut points = points::get(&data);
    points::sort(&mut points);

    let result = sudoku::solve(&data, &mut points, 0);
    if result[0][0] == -1 {
        println!("\nInvalid clause!");
        return;
    }

    let valid = test::validate(&result);


    if valid {
        input::output(&result);
    } else {
        eprintln!("Validation failed");
    }
}

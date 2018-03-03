use std::fs::File;
use std::io::prelude::*;
use std::env;

pub fn get() -> Vec<Vec<i8>> {
    let exe_path = env::current_exe().unwrap();
    let path = exe_path.parent().unwrap().join("files/input.txt");
    let mut file = File::open(&path).expect("Can't open input file");

    let mut input = String::new();
    file.read_to_string(&mut input).expect("Can't read from input file");

    let mut parsed: Vec<Vec<i8>> = Vec::new();

    for line in input.lines() {
        let iter = line.split_whitespace();
        let mut parsed_line = Vec::new();
        for val in iter {
            let value: i8 = val.parse().unwrap();
            parsed_line.push(value);
        }
        parsed.push(parsed_line);
    }

    parsed
}

pub fn output(result: &Vec<Vec<i8>>) {
    let mut result_string = String::new();

    for vec in result {
        for val in vec {
            let mut val_string = val.to_string();
            val_string.push(' ');
            result_string.push_str(&*val_string);
        }
        result_string.push_str("\n");
    }

    println!("{}", result_string);
}

fn main() {
    let res = summy("A3", "C3");
    println!("{}", res);
}

fn summy(cell1: &str, cell2: &str) -> bool {
    let letters = ["A", "B", "C", "D", "E", "F", "G", "H"];
    let letters = letters.into_iter();

    let cell1_l = &cell1[0..1];
    let cell2_l = &cell2[0..1];

    let mut cell1_sum: i8 = 0;
    let mut cell2_sum: i8 = 0;

    cell1_sum += cell1[1..2].to_string().parse::<i8>().unwrap();
    cell2_sum += cell2[1..2].to_string().parse::<i8>().unwrap();

    for (index, value) in letters.enumerate() {
        let index = index as i8;
        let str_val = value.to_string();
        if cell1_l == str_val { cell1_sum += index }
        if cell2_l == str_val { cell2_sum += index }
    }


    if cell1_sum % 2 == cell2_sum % 2 { return true }
    else { false }
}

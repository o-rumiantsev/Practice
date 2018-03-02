#[derive(Debug)]
pub struct Point {
    x: usize,
    y: usize,
    vals: Vec<i8>,
    weight: i8
}

impl Point {
    fn new(x: usize, y: usize) -> Point {
        Point {
            x, y, vals: Vec::new(), weight: 0
        }
    }
}


fn square_coords(x: usize, y: usize) -> (usize, usize, usize, usize) {
    let x1: usize = (x / 3) * 3;
    let x2: usize = x1 + 3;
    let y1: usize = (y / 3) * 3;
    let y2: usize = y1 + 3;
    (x1, y1, x2, y2)
}

fn predict(data: &Vec<Vec<i8>>, point: &mut Point) {
    let mut possible_values = vec![1, 2, 3, 4, 5, 6, 7, 8, 9];
    let x = point.x;
    let y = point.y;

    for i in 0..9 {
        if data[i][x] != 0 {

        }
    }

    for j in 0..9 {
        if data[y][j] != 0 {

        }
    }

    let (x1, y1, x2, y2) = square_coords(x, y);
    for i in y1..y2 {
        for j in x1..x2 {
            if
                data[i][j] != 0 &&
                i != y &&
                j != x
            {

            }
        }
    }

    println!("{:?}", possible_values);
}


pub fn get(data: &Vec<Vec<i8>>) -> Vec<Point> {
    let mut points: Vec<Point> = Vec::new();

    for y in 0..9 {
        for x in 0..9 {
            let mut p = Point::new(x, y);
            if data[y][x] == 0 {
                for i in 0..9 {
                    if data[i][x] != 0 && i != y {
                        p.weight = p.weight + 1;
                    }
                }

                for j in 0..9 {
                    if data[y][j] != 0 && j != x {
                        p.weight = p.weight + 1;
                    }
                }

                let (x1, y1, x2, y2) = square_coords(x, y);
                for i in y1..y2 {
                    for j in x1..x2 {
                        if
                            data[i][j] != 0 &&
                            i != y &&
                            j != x
                        {
                            p.weight = p.weight + 1;
                        }
                    }
                }

                predict(&data, &mut p);
                points.push(p);
            }
        }
    };

    points
}


pub fn sort(points: &mut Vec<Point>) {
    let len = points.len();
    for i in 1..len {
        let mut j = i;
        while j > 0 {
            if points[j - 1].weight < points[j].weight {
                points.swap(j - 1, j);
                j -= 1;
            } else {
                break;
            }
        }
    }
}

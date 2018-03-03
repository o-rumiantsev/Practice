pub mod input;
pub mod points;
pub mod test;

pub fn solve(data: &Vec<Vec<i8>>, points: &Vec<points::Point>, pn: usize) -> Vec<Vec<i8>> {
    let mut copy: Vec<Vec<i8>> = data.to_vec();
    if pn == points.len() {
        return copy;
    }

    let mut valid = false;
    for val in &points[pn].vals {
        if points::validate(&data, points[pn].x, points[pn].y, *val) {
            valid = true;
            substitute(&mut copy, &points[pn], *val);
            copy = solve(&copy, &points, pn + 1);
            if copy[0][0] == -1 {
                valid = false;
                copy = data.to_vec();
            } else {
                break;
            }
        }
    }

    if !valid {
        return vec![vec![-1]];
    }

    return copy;
}

fn substitute(copy: &mut Vec<Vec<i8>>, point: &points::Point, val: i8) {
    let x = point.x;
    let y = point.y;
    copy[y][x] = val;
}

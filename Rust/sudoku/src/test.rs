pub fn validate(mtrx: &Vec<Vec<i8>>) -> bool {
    let columns = valid_col(&mtrx);
    let rows = valid_row(&mtrx);
    let squares = valid_sqr(&mtrx);

    if columns && rows && squares {
        return true;
    }

    false
}

fn valid_row(mtrx: &Vec<Vec<i8>>) -> bool {
    for row in mtrx {
        if row.capacity() != 9 {
            return false;
        }

        for num in 1..10 {
           if !row.contains(&num) {
               return false;
           }
        }
    }

    true
}

fn valid_col(mtrx: &Vec<Vec<i8>>) -> bool {
    if mtrx.capacity() != 9 {
        return false;
    }

    for i in 0..9 {
        let mut col = Vec::new();

        for row in mtrx {
           col.push(row[i]);
        }

        for num in 1..10 {
            if !col.contains(&num) {
                return false;
            }
        }
    }

    true
}

fn valid_sqr(mtrx: &Vec<Vec<i8>>) -> bool {
    let mut row_offset = 0;
    let mut col_offset = 0;

    while row_offset < 9 {
        while col_offset < 9 {
            let mut sqr = Vec::new();

            for i in row_offset..row_offset + 3 {
                for j in col_offset..col_offset + 3 {
                    sqr.push(mtrx[i][j])
                }
            }

            for num in 1..10 {
                if !sqr.contains(&num) {
                    return false;
                }
            }

            col_offset += 3;
        }

        col_offset = 0;
        row_offset += 3;
    }

    true
}

pub fn new() -> Graph {
    Graph {
        vertexs: Vec::new()
    }
}

fn get_max_weight_edge<'a>(
    vertexs: &'a Vec<Vec<u32>>, indexes: &Vec<usize>
) -> (usize, &'a Vec<u32>) {
    let mut max_index: usize = 0;
    let mut max_weight: u32 = 0;
    let mut index: usize = 0;
    let mut i: usize = 0;

    for v in vertexs {
        let idx = v[0] as usize;
        if indexes.contains(&idx) {
            i += 1;
            continue;
        };

        if v[1] >= max_weight {
            index = i;
            max_index = idx;
            max_weight = vertexs[index][1];
        }
        i += 1;
    }

    return (max_index, &vertexs[index]);
}

fn get_min_weight_edge<'a>(
    vertexs: &'a Vec<Vec<u32>>, indexes: &Vec<usize>
) -> (usize, &'a Vec<u32>) {
    let mut max_index: usize = 0;
    let mut min_weight: u32 = <u32>::max_value();
    let mut index: usize = 0;
    let mut i: usize = 0;

    for v in vertexs {
        let idx = v[0] as usize;
        if indexes.contains(&idx) {
            i += 1;
            continue;
        };

        if v[1] <= min_weight {
            index = i;
            max_index = idx;
            min_weight = vertexs[index][1];
        }
        i += 1;
    }

    return (max_index, &vertexs[index]);
}


#[derive(Debug)]
pub struct Graph {
    vertexs: Vec<Vec<Vec<u32>>>
}

impl Graph {
    pub fn add(&mut self, vertex: Vec<Vec<u32>>) {
        self.vertexs.push(vertex)
    }

    pub fn print(&self) {
        let mut index: usize = 0;
        for vertex in &self.vertexs {
            for v in vertex {
                println!("[{}] ---- {} ---- [{}]", index, v[1], v[0]);
            }
            index += 1;
        }
    }

    fn get_max_for_indexes(&self, vertexs_indexes: &Vec<usize>) -> (usize, u32) {
        let mut index: usize = 0;
        let mut weight: u32 = 0;

        for i in vertexs_indexes {
            let (k, vertex) = get_max_weight_edge(&self.vertexs[*i], vertexs_indexes);
            let idx = vertex[0] as usize;
            if !vertexs_indexes.contains(&idx) && vertex[1] > weight {
                weight = vertex[1];
                index = k;
            }
        }


        return (index, weight);
    }

    fn get_min_for_indexes(&self, vertexs_indexes: &Vec<usize>) -> (usize, u32) {
        let mut index: usize = 0;
        let mut weight: u32 = <u32>::max_value();

        for i in vertexs_indexes {
            let (k, vertex) = get_min_weight_edge(&self.vertexs[*i], vertexs_indexes);
            let idx = vertex[0] as usize;
            if !vertexs_indexes.contains(&idx) && vertex[1] < weight {
                weight = vertex[1];
                index = k;
            }
        }


        return (index, weight);
    }


    pub fn find_max_tree(&self) {
        let mut cur_index: usize = 0;
        let mut total_weight: u32 = 0;
        let mut vertexs_indexes: Vec<usize> = vec![0];

        let (mut index, mut weight) = self.get_max_for_indexes(&vertexs_indexes);
        total_weight += weight;

        println!(
            "[{}] ---- {} ----> [{}]   Total weight {}", cur_index, weight, index, total_weight
        );

        cur_index = index;
        while index != 0 {
            vertexs_indexes.push(index);
            let res = self.get_max_for_indexes(&vertexs_indexes);
            index = res.0;
            weight = res.1;

            if index != 0 {
                total_weight += weight;
                println!(
                    "[{}] ---- {} ----> [{}]   Total weight {}",
                    cur_index, weight, index, total_weight
                );
            }

            cur_index = index;
        }

        println!("Total {}",total_weight);
    }

    pub fn find_min_tree(&self) {
        let mut cur_index: usize = 0;
        let mut total_weight: u32 = 0;
        let mut vertexs_indexes: Vec<usize> = vec![0];

        let (mut index, mut weight) = self.get_min_for_indexes(&vertexs_indexes);
        total_weight += weight;

        println!(
            "[{}] ---- {} ----> [{}]   Total weight {}", cur_index, weight, index, total_weight
        );

        cur_index = index;
        while index != 0 {
            vertexs_indexes.push(index);
            let res = self.get_min_for_indexes(&vertexs_indexes);
            index = res.0;
            weight = res.1;

            if index != 0 {
                total_weight += weight;
                println!(
                    "[{}] ---- {} ----> [{}]   Total weight {}",
                    cur_index, weight, index, total_weight
                );
            }

            cur_index = index;
        }

        println!("Total {}",total_weight);
    }
}

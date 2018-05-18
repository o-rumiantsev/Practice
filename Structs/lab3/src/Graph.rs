pub fn new() -> Graph {
    Graph {
        vertexs: Vec::new()
    }
}

fn get_max_weight_edge<'a>(
    vertexs: &'a Vec<Vec<u32>>, indexes: &Vec<usize>
) -> (usize, &'a Vec<u32>) {
    // println!("{:?}", vertexs);
    let mut max_index: usize = 0;
    let mut index: usize = 0;
    let mut i: usize = 0;

    for v in vertexs {
        let idx = v[0] as usize;
        if indexes.contains(&idx) {
            // println!("{} {:?}", idx, indexes);
            i += 1;
            continue;
        };

        if v[1] >= vertexs[max_index][1] {
            max_index = idx;
            index = i;
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

    fn get_max_for_indexes(&self, graph: &Graph, vertexs_indexes: &Vec<usize>) -> (usize, u32) {
        // println!("{:?}", vertexs_indexes);
        let mut index: usize = 0;
        let mut weight: u32 = 0;

        for i in vertexs_indexes {
            let (k, vertex) = get_max_weight_edge(&graph.vertexs[*i], vertexs_indexes);
            // println!("{} {:?}", k, vertex);
            let idx = vertex[0] as usize;
            if !vertexs_indexes.contains(&idx) && vertex[1] > weight {
                // println!("{:?}", vertex);
                weight = vertex[1];
                index = k;
            }
        }


        return (index, weight);
    }

    pub fn find_max_tree(&self) {
        let mut graph = new();
        let mut total_weight: u32 = 0;
        let mut vertexs_indexes: Vec<usize> = vec![0];

        let (mut index, mut weight) = graph.get_max_for_indexes(self, &vertexs_indexes);
        total_weight += weight;
        println!("======= {} - {} ======", index, weight);

        while index != 0 {
            vertexs_indexes.push(index);
            let res = graph.get_max_for_indexes(self, &vertexs_indexes);
            index = res.0;
            weight = res.1;

            if index != 0 {
                total_weight += weight;
                println!("Total weight {}", total_weight);
                println!("======= {} - {} ======", index, weight);
            }
        }

        println!("weight {}",total_weight);
    }
    //
    // pub fn find_min_tree() -> Graph {
    //
    // }
}

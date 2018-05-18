extern crate lab3;

use lab3::Graph;

fn gen_graph() -> Graph::Graph {
    let mut graph = Graph::new();

    graph.add(vec![vec![1, 2], vec![3, 1]]);                                                 // V0
    graph.add(vec![vec![0, 2], vec![2, 4], vec![3, 3], vec![4, 8]]);                         // V1
    graph.add(vec![vec![1, 4], vec![4, 7]]);                                                 // V2
    graph.add(vec![vec![0, 1], vec![1, 3], vec![4, 5]]);                                     // V3
    graph.add(vec![vec![3, 5], vec![2, 7], vec![1, 8], vec![5, 3], vec![6, 1], vec![7, 2]]); // V4
    graph.add(vec![vec![4, 3]]);                                                             // V5
    graph.add(vec![vec![4, 1], vec![7, 8]]);                                                 // V6
    graph.add(vec![vec![6, 8], vec![4, 2]]);                                                 // V7

    return graph;
}

fn main() {
    let graph = gen_graph();
    graph.print();
    println!();

    graph.find_max_tree();
    println!();

    graph.find_min_tree();
}

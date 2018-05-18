extern crate lab3;

use lab3::Graph;

fn gen_graph() -> Graph::Graph {
    let mut graph = Graph::new();

    graph.add(vec![vec![1, 1], vec![5, 2]]);                         // Vertex 0
    graph.add(vec![vec![0, 1], vec![2, 5], vec![5, 4], vec![4, 6]]); // Vertex 1
    graph.add(vec![vec![1, 5]]);                                     // Vertex 2
    graph.add(vec![vec![4, 2]]);                                     // Vertex 3
    graph.add(vec![vec![3, 2], vec![1, 6], vec![5, 3]]);             // Vertex 4
    graph.add(vec![vec![0, 2], vec![1, 4], vec![4, 3]]);             // Vertex 5

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

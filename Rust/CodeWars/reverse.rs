fn main() {
  let rev = reverse("world");
  println!("{}", rev);
}

fn reverse(source: &str) -> String {
  source.chars().rev().collect::<String>()
}

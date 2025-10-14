use ppc::data_generator;
use std::time::Instant;

#[test]
fn cp1_test_1() {
    use ppc::cp1::correlate;
    let ny = 2;
    let nx = 2;
    let data: Vec<f32> = vec![1., -1., -1., 1.];
    let mut result = vec![0.0f32; ny * ny];
    correlate(ny, nx, &data, &mut result);
    // println!("result={:#?}", result);
    assert!(result[1] < 0.0);
    assert_eq!(result[0], 1.);
    assert_eq!(result[3], 1.);
}

#[test]
fn test_cp1vcp2a() {
    use ppc::cp1;
    use ppc::cp2a;
    let ny = 100;
    let nx = 100;
    let data = data_generator(ny, nx);
    let mut result_1 = vec![0.0f32; ny * ny];
    let start = Instant::now();
    cp1::correlate(ny, nx, &data, &mut result_1);
    let duration_1 = start.elapsed();
    println!("test_4 (cp1) duration = {duration_1:?}");

    let mut result_2 = vec![0.0f32; ny * ny];
    let start = Instant::now();
    cp2a::correlate(ny, nx, &data, &mut result_2);
    let duration_2 = start.elapsed();
    println!("test_4 (cp2a) duration = {duration_2:?}");
    assert_eq!(result_1, result_2);
}

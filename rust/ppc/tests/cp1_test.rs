use ppc::data_generator;

#[test]
fn cp1_test_1() {
    use ppc::cp1::correlate;
    let ny = 2;
    let nx = 2;
    let data: Vec<f32> = vec![1., -1., -1., 1.];
    let mut result = vec![0.0f32; ny * ny];
    correlate(ny, nx, &data, &mut result);
    println!("result={:#?}", result);
    assert!(result[1] < 0.0);
    assert_eq!(result[0], 1.);
    assert_eq!(result[3], 1.);
}

#[test]
fn cp1_test_2() {
    use ppc::cp1::correlate;
    let ny = 2;
    let nx = 2;
    let data = data_generator(ny, nx);
    let mut result = vec![0.0f32; ny * ny];
    correlate(ny, nx, &data, &mut result);
    assert_eq!(result[0], 1.);
    assert!(result[1] != 0.0);
}

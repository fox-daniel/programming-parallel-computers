use ndarray::Array1;
use ndarray_rand::RandomExt;
use rand_distr::Uniform;

pub mod cp1;

pub fn data_generator(row_size: usize, column_size: usize) -> Vec<f32> {
    Array1::random(row_size * column_size, Uniform::new(-100., 100.)).to_vec()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let m = data_generator(2, 2);
        assert!(m[3] > -100.0);
        assert!(m[3] <= 100.0);
    }
}

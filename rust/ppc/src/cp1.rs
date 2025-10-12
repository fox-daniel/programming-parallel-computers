fn normalize_rows(a: usize, nx: usize, data: &Vec<f64>, normalized: &mut Vec<f64>) {
    let mut mean: f64 = 0.;
    let mut len: f64 = 0.;
    for k in 0..nx {
        mean += data[k + a * nx];
    }

    mean = mean / (nx as f64);
    for k in 0..nx {
        normalized[k + a * nx] = data[k + a * nx] - mean;
    }

    for k in 0..nx {
        len += normalized[k + a * nx] * normalized[k + a * nx];
    }
    len = len.sqrt();
    if len > 0.0 {
        for k in 0..nx {
            normalized[k + a * nx] = normalized[k + a * nx] / len;
        }
    }
}

fn correlate_rows(a: usize, b: usize, nx: usize, normalized: &Vec<f64>) -> f32 {
    let mut correlation: f64 = 0.;
    for i in 0..nx {
        correlation += normalized[i + nx * a] * normalized[i + nx * b];
    }
    return correlation as f32;
}

/*
This is the function you need to implement. Quick reference:
- input rows: 0 <= y < ny
- input columns: 0 <= x < nx
- element at row y and column x is stored in data[x + y*nx]
- correlation between rows i and row j has to be stored in result[i + j*ny]
- only parts with 0 <= j <= i < ny need to be filled
*/
pub fn correlate(ny: usize, nx: usize, data: &Vec<f32>, result: &mut Vec<f32>) {
    let mut normalized: Vec<f64> = vec![0.0f64; ny * nx];
    let data_64: Vec<f64> = data.into_iter().map(|x| *x as f64).collect();
    for i in 0..ny {
        normalize_rows(i, nx, &data_64, &mut normalized);
    }
    for i in 0..ny {
        for j in 0..=i {
            result[i + j * ny] = correlate_rows(i, j, nx, &normalized);
        }
    }
}

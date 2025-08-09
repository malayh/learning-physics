use rand::Rng;

pub struct GameOfLife {
    pub state: Vec<Vec<u32>>,
}

impl GameOfLife {
    pub fn new(rows: usize, cols: usize) -> Self {
        GameOfLife {
            state: vec![vec![0; cols]; rows],
        }
    }

    pub fn init(&mut self, initial_state: Vec<Vec<u32>>) {
        if initial_state.len() == self.state.len() && initial_state[0].len() == self.state[0].len() {
            self.state = initial_state;
        } else {
            panic!("Initial state dimensions do not match the game board size.");
        }
    }

    pub fn size(&self) -> (usize, usize) {
        (self.state.len(), self.state[0].len())
    }

    fn activate_cell(&mut self, row: usize, col: usize, value: u32) {
        if row < self.state.len() && col < self.state[0].len() {
            self.state[row][col] = value;
        }
    }
    fn deactivate_cell(&mut self, row: usize, col: usize) {
        if row < self.state.len() && col < self.state[0].len() {
            self.state[row][col] = 0;
        }
    }
    fn get_cell(&self, row: usize, col: usize) -> u32 {
        if row < self.state.len() && col < self.state[0].len() {
            self.state[row][col]
        } else {
            0
        }
    }

    pub fn next(&mut self) {
        let mut new_state = self.state.clone();
        let directions = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)];

        for i in 0..self.state.len() {
            for j in 0..self.state[i].len() {
                let mut live_neighbors = 0;

                for (dx, dy) in &directions {
                    let ni = i as isize + dx;
                    let nj = j as isize + dy;

                    if ni >= 0 && ni < self.state.len() as isize && nj >= 0 && nj < self.state[i].len() as isize {
                        live_neighbors += self.get_cell(ni as usize, nj as usize);
                    }
                }

                if self.get_cell(i, j) > 0  {
                    // Cell is alive
                    if live_neighbors < 2 || live_neighbors > 3 {
                        new_state[i][j] = 0; // Cell dies
                    }
                } else {
                    // Cell is dead
                    if live_neighbors == 3 {
                        new_state[i][j] = 1; // Cell becomes alive
                    }
                }
                
            }

        } 



        self.state = new_state;
    }
    pub fn render(&self) {
        print!("\x1B[2J\x1B[1;1H");

        for row in &self.state {
            for &cell in row {
                print!("{} ", if cell > 0 { "■" } else { " " });
            }
            println!();
        }
    }

}


pub fn random_game(rows: usize, cols: usize) -> GameOfLife {
    let mut rng = rand::thread_rng();
    let mut state = vec![vec![0; cols]; rows];
    for i in 0..rows {
        for j in 0..cols {
            state[i][j] = rng.gen_range(0..=1);
        }
    }
    let mut game = GameOfLife::new(rows, cols);
    game.init(state);
    
    game
}

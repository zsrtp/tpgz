use std::path::PathBuf;

#[derive(StructOpt, Debug)]
pub struct Opt {
    #[structopt(short = "I")]
    pub input: PathBuf,
    #[structopt(short = "S")]
    pub size: Option<f32>,
    #[structopt(short = "O")]
    pub output: Option<PathBuf>,
    #[structopt(short = "N")]
    pub name: Option<String>,
}

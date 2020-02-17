#![feature(proc_macro_hygiene)]
#[macro_use]
extern crate structopt;
extern crate worker as gcn_fonts;

mod opt;

use std::fs;
use std::io::prelude::*;
use std::path::PathBuf;

use opt::Opt;

use gcn_fonts::prelude::*;
use structopt::StructOpt;

fn main() {
    let opt: Opt = Opt::from_args();

    println!("{:?}", &opt);
    let name = opt
        .input
        .file_stem()
        .map(|s| s.to_str().unwrap())
        .map(|s| String::from(s))
        .unwrap();
    let output = opt.output.unwrap_or(PathBuf::from("build"));
    let font_name = opt.name.unwrap_or(name);

    let font = gcn_fonts::work(Params {
        path: String::from(opt.input.to_string_lossy()),
        resolution: None,
        size: match opt.size {
            Some(s) => Some(Size { size: s }),
            None => None,
        },
    });

    {
        fs::create_dir_all(&output).unwrap(); 

        let mut f = fs::File::create(output.join("consolas.c")).unwrap();

        let mut idx = 0;
        for byte in font.data {
            if idx == 0 {
                write!(
                    f,
                    "const char consolas_bytes[]  __attribute__ ((aligned (32))) = {{\n    0x{:X}",
                    byte
                )
                .unwrap();
            } else {
                write!(f, ", 0x{:X}", byte).unwrap();
            }
            idx += 1;
            if idx % 30 == 0 {
                write!(f, "\n    ").unwrap();
            }
        }
        write!(f, "}};").unwrap();
        let mut f =
            fs::File::create(output.join(format!("{}.h", font_name.to_lowercase()))).unwrap();

        write!(
            f,
            r#"#ifndef __{}_H_
#define __{}_H_
#include "font.h"

//extern char _{}_start;
//extern char _{}_end;
extern char {}_bytes[];

const static _Font f_{} {{
    {}.0, {}.0, {:?}, {:?},
    {{
"#,
            font_name.to_uppercase(),
            font_name.to_uppercase(),
            font_name.to_lowercase(),
            font_name.to_lowercase(),
            font_name.to_lowercase(),
            font_name,
            font.width,
            font.height,
            font.size,
            font.space_advance,
        )
        .unwrap();

        font.glyphs.iter().for_each(|r| {
            writeln!(
                f,
                "\t\t{{{}, {}, {}, {}, {}}},",
                r.descender, r.bounds.min.x, r.bounds.min.y, r.bounds.max.x, r.bounds.max.y
            )
            .unwrap();
        });

        write!(
            f,
            r#"    }},
    0 //&_{}_start
}};

#endif // __{}_H_"#,
            font_name.to_lowercase(),
            font_name.to_uppercase()
        )
        .unwrap();
    }
    // let output_bin = output.join(format!("{}.bin", font_name.to_lowercase()));
    // let mut f = fs::File::create(&output_bin).unwrap();
    // f.write_all(&FONT.data).unwrap();
    //     let output_obj = output.join(format!("{}.o", font_name.to_lowercase()));
    //     match std::process::Command::new("powerpc-eabi-objcopy")
    //         .args(&[
    //             "-I",
    //             "binary",
    //             "-O",
    //             "elf32-powerpc",
    //             "-B",
    //             "powerpc",
    //             "--section-alignment",
    //             "32",
    //             "--file-alignment",
    //             "32",
    //             "--redefine-sym",
    //             &format!(
    //                 "_binary_build_{}_bin_start=_{}_start",
    //                 font_name.to_lowercase(),
    //                 font_name.to_lowercase()
    //             ),
    //             "--redefine-sym",
    //             &format!(
    //                 "_binary_build_{}_bin_end=_{}_end",
    //                 font_name.to_lowercase(),
    //                 font_name.to_lowercase()
    //             ),
    //             &output_bin.to_string_lossy(),
    //             &output_obj.to_string_lossy(),
    //         ])
    //         .spawn()
    //     {
    //         Ok(_) => {}
    //         Err(_) => println!(
    //             "Unable to execute objcopy command.Please run the following to build your object:
    // \tpowerpc-eabi-objcopy -I binary -O elf32-powerpc -B powerpc --redefine-sym _binary_build_{}_bin_start=_{}_start {}.bin {}.o",
    //             &output_bin.to_string_lossy(),
    //             &output_obj.to_string_lossy(),
    //             font_name.to_lowercase(),
    //             font_name.to_lowercase()
    //         ),
    //     };
}

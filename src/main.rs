use rusty_v8 as v8;
mod runnable;

fn main() {
    let platform = v8::new_default_platform().unwrap();
    v8::V8::initialize_platform(platform);
    v8::V8::initialize();

    let result = runnable::run(String::from("console.log('gg')"));

    println!("{}", result)
}
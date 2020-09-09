use rusty_v8 as v8;
mod runnable;

fn main() {
    let platform = v8::new_default_platform().unwrap();
    v8::V8::initialize_platform(platform);
    v8::V8::initialize();

    //let mut isolate = v8::Isolate::new(v8::CreateParams::default().heap_limits(0, 10000));
    let mut iso = runnable::default_isolate();
    let mut worker = runnable::Worker::new(&mut iso);

    worker.globals.push(runnable::Global{
        key: v8::Local::from(v8::String::new(&mut worker.scope, "owo").unwrap()), 
        value: v8::Local::from(v8::String::new(&mut worker.scope, "awa").unwrap())
    });

    let result = worker.run(String::from("
    const x = (num1, num2) => {
        return num1 + num2
    }

    //x(6, 4)
    owo
    "));

    // let result = runnable::run(String::from("
    // const x = (num1, num2) => {
    //     return num1 + num2
    // }

    // //x(6, 4)
    // owo
    // "));

    println!("{}", result)
}
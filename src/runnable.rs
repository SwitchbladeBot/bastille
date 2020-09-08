use rusty_v8 as v8;

pub fn run(code: String) -> String {
    let isolate = &mut v8::Isolate::new(v8::CreateParams::default().heap_limits(0, 10000));
    
    let scope = &mut v8::HandleScope::new(isolate);
    let context = v8::Context::new(scope);
    let scope = &mut v8::ContextScope::new(scope, context);

    let code = v8::String::new(scope, &code[..]).unwrap();
    let result = v8::Script::compile(scope, code, None).unwrap().run(scope).unwrap().to_string(scope).unwrap();

    result.to_rust_string_lossy(scope)
}
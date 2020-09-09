use rusty_v8 as v8;

pub struct Worker<'a> {
    pub globals: Vec<Global<'a>>,
    pub scope: v8::HandleScope<'a, ()>,
}

pub struct Global<'a> {
    pub key: v8::Local<'a, v8::Name>,
    pub value: v8::Local<'a, v8::Data>,
}

pub fn default_isolate() -> v8::OwnedIsolate {
    v8::Isolate::new(v8::CreateParams::default().heap_limits(0, 10000))
}

impl<'a> Worker<'a> {
    pub fn new(isolate: &'a mut v8::OwnedIsolate) -> Self {
        Worker {
            globals: Vec::new(),
            scope: v8::HandleScope::new(isolate),
        }
    }
    pub fn run(&mut self, code: String) -> String {
        let global = v8::ObjectTemplate::new(&mut self.scope);

        for g in self.globals.iter() {
            global.set(g.key, g.value);
        }
     
        let context = v8::Context::new_from_template(&mut self.scope, global);
        let scope = &mut v8::ContextScope::new(&mut self.scope, context);

        let code = v8::String::new(scope, &code[..]).unwrap();
        let result = v8::Script::compile(scope, code, None).unwrap().run(scope).unwrap().to_string(scope).unwrap();

        result.to_rust_string_lossy(scope)
    }
}
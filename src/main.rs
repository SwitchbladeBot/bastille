use actix_web::{web, App, HttpResponse, HttpServer, Responder};
use actix_rt;
use rusty_v8 as v8;

async fn index(info: web::Path<String>) -> impl Responder {
    let isolate = &mut v8::Isolate::new(Default::default());

    let scope = &mut v8::HandleScope::new(isolate);
    let context = v8::Context::new(scope);
    let scope = &mut v8::ContextScope::new(scope, context);

    let code = v8::String::new(scope, &**info).unwrap();
    let mut result = v8::Script::compile(scope, code, None).unwrap().run(scope).unwrap().to_string(scope).unwrap();

    HttpResponse::Ok().body(result.to_rust_string_lossy(scope))
}

#[actix_rt::main]
async fn main() -> std::io::Result<()> {
    let platform = v8::new_default_platform().unwrap();
    v8::V8::initialize_platform(platform);
    v8::V8::initialize();

    HttpServer::new(|| {
        App::new()
            .route("/{code}", web::get().to(index))
    })
        .bind("127.0.0.1:8088")?
        .run()
        .await
}

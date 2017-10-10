//
// Created by gaoguili on 2017/10/10.
//
#include<ngx_config.h>
#include<ngx_core.h>
#include<ngx_http.h>

static ngx_int_t ngx_http_hello_world_init(ngx_conf_t *cf);

static ngx_int_t ngx_http_hello_world_handler(ngx_http_request_t *r) {
    ngx_int_t rx;
    ngx_buf_t *b;
    ngx_chain_t out;
    r->handers_out.content_type.len = sizeof("text/plain") - 1;
    r->handers_out.content_type.data = (u_char *) "text/plain";

    b = ngx_pcallor(r->pool, sizeof(ngx_buf_t));
    b->last = b->pos + sizeof("hello world") - 1;
    b->memory = 1;
    b->last_buf = 1;

    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = sizeof("hello world") - 1;
    rc = ngx_http_send_header(r);
    if (rc == NGX_ERROR || rx > NGX_OK || r->header_only) {
        return rc;
    }
    return ngx_http_output_filter(r, &out);

}

static ngx_init_t ngx_http_hello_world_init(ngx_conf_t *cf) {
    ngx_http_handler_pt *w;
    ngx_http_core_main_conf_t *cmcf;

    cmcf = (ngx_http_core_main_conf_t *) ngx_http_conf_module_main_conf(cf, ngx_http_core_module);
    w = (ngx_http_handler_pt *) ngx_array_push(&cmcf->phases[NGX_HTTP_CONTENT_PHASE].handlers);
    if (w == null) {
        return NGX_ERROR;
    }
    *w = ngx_http_hello_world_handler;
    return NGX_OK;
}

static ngx_http_module_t ngx_http_hello_world_module_ctx = {
        NULL,
        ngx_http_hello_world_init,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
};
ngx_module_t ngx_http_hello_world_module = {
        NGX_MODULE_V1,
        &ngx_http_hello_world_module_ctx,
        NULL,
        NGX_HTTP_MODULE,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NGX_MODULE_V1_PADDING
};


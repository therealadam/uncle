#include "ruby.h"
#include "unqlite.h"

// Wrapper around unqlite to make Ruby's Data_*_Struct API's happy
typedef struct _uncle {
  unqlite *db;
} uncle;

void check_unqlite_result(uncle* u, int result) {
  if (result != UNQLITE_OK) {
    const char *reason;
    int len;

    unqlite_config(u->db, UNQLITE_CONFIG_ERR_LOG, &reason, &len);
    if (len > 0) { puts(reason); }
    // TODO raise exception
  }
}

static VALUE uncle_init(VALUE self, VALUE name) {
  uncle *u;
  int result;

  Data_Get_Struct(self, uncle, u);
  result = unqlite_open(&u->db, RSTRING_PTR(name), UNQLITE_OPEN_CREATE);
  check_unqlite_result(u, result);

  result = unqlite_kv_store(u->db, "test", -1, "Hello world", 11); // HAX
  check_unqlite_result(u, result);

  return self;
}

static VALUE uncle_close(VALUE self) {
  uncle *u;
  int result;

  Data_Get_Struct(self, uncle, u);
  result = unqlite_commit(u->db);
  check_unqlite_result(u, result);

  return Qnil;
}

static void deallocate(void *ptr) {
  int result;
  uncle *u;

  u = (uncle *) ptr;
  result = unqlite_close(u->db);
  check_unqlite_result(u, result);

  free(u);
  return;
}

static VALUE allocate(VALUE klass) {
  uncle *u;
  VALUE obj;

  obj = Data_Make_Struct(klass, uncle, NULL, deallocate, u);
  return obj;
}

VALUE cDB;
void Init_uncle() {
  VALUE mUncle;

  mUncle = rb_define_module("Uncle");
  cDB    = rb_define_class_under(mUncle, "DB", rb_cObject);

  rb_define_method(cDB, "initialize", uncle_init, 1);
  rb_define_method(cDB, "close", uncle_close, 0);
  rb_define_alloc_func(cDB, allocate);
}


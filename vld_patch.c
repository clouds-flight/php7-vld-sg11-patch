--- vld.c	2020-01-14 01:12:09.000000000 +0800
+++ vld_modify.c	2020-09-20 12:56:52.982420619 +0800
@@ -299,20 +299,6 @@ static zend_op_array *vld_compile_file(z
 
 	op_array = old_compile_file (file_handle, type TSRMLS_CC);
 
-	if (VLD_G(path_dump_file)) {
-		fprintf(VLD_G(path_dump_file), "subgraph cluster_file_%p { label=\"file %s\";\n", op_array, op_array->filename ? ZSTRING_VALUE(op_array->filename) : "__main");
-	}
-	if (op_array) {
-		vld_dump_oparray (op_array TSRMLS_CC);
-	}
-
-	zend_hash_apply_with_arguments (CG(function_table) TSRMLS_CC, (apply_func_args_t) VLD_WRAP_PHP7(vld_dump_fe), 0);
-	zend_hash_apply (CG(class_table), (apply_func_t) VLD_WRAP_PHP7(vld_dump_cle) TSRMLS_CC);
-
-	if (VLD_G(path_dump_file)) {
-		fprintf(VLD_G(path_dump_file), "}\n");
-	}
-
 	return op_array;
 }
 /* }}} */
@@ -325,21 +311,42 @@ static zend_op_array *vld_compile_string
 
 	op_array = old_compile_string (source_string, filename TSRMLS_CC);
 
-	if (op_array) {
-		vld_dump_oparray (op_array TSRMLS_CC);
-
-		zend_hash_apply_with_arguments (CG(function_table) TSRMLS_CC, (apply_func_args_t) vld_dump_fe_wrapper, 0);
-		zend_hash_apply (CG(class_table), (apply_func_t) vld_dump_cle_wrapper TSRMLS_CC);
-	}
-
 	return op_array;
 }
 /* }}} */
-
+int execute_time=0;
 /* {{{
  *    This function provides a hook for execution */
 static void vld_execute_ex(zend_execute_data *execute_data TSRMLS_DC)
 {
-	// nothing to do
+
+	if (execute_time == 1)
+	{
+		zend_op_array *op_array;
+
+		op_array=&execute_data->func->op_array;
+
+		if (VLD_G(path_dump_file))
+		{
+			fprintf(VLD_G(path_dump_file), "subgraph cluster_file_%p { label=\"file %s\";\n", op_array, op_array->filename ? ZSTRING_VALUE(op_array->filename) : "__main");
+		}
+		if (op_array)
+		{
+			vld_dump_oparray(op_array TSRMLS_CC);
+		}
+
+		zend_hash_apply_with_arguments(CG(function_table) TSRMLS_CC, (apply_func_args_t)VLD_WRAP_PHP7(vld_dump_fe), 0);
+		zend_hash_apply(CG(class_table), (apply_func_t)VLD_WRAP_PHP7(vld_dump_cle) TSRMLS_CC);
+
+		if (VLD_G(path_dump_file))
+		{
+			fprintf(VLD_G(path_dump_file), "}\n");
+		}
+
+		return;
+	}
+
+	execute_time = 1;
+	old_execute_ex(execute_data);
 }
 /* }}} */

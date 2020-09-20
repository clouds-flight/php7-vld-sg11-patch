# php vld扩展显示sg11组建解密后的opcodes的补丁

1.将vld_patch.c 和srm_oparray_patch.c 拷贝到vld扩展源码根目录下

2.执行
  patch -p0 < vld_patch.c
  patch -p0 < srm_oparray_patch.c

3.参照正常的编译vld扩展进行编译安装即可

4.需将php.ini vld扩展参数vld.execute设置为0时才有效

# Copyright (c) 2022 Unionman Technology Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#!/usr/bin/env sh

root_src_dir=$(pwd)

pushd ${root_src_dir}
cp ${root_src_dir}/device/board/unionman/a311d/loader/images/* ${root_src_dir}/out/a311d/packages/phone/images -rvf
${root_src_dir}/device/board/unionman/a311d/tools/linux/aml_image_v2_packer -r ${root_src_dir}/out/a311d/packages/phone/images/openharmony.conf ${root_src_dir}/out/a311d/packages/phone/images/ ${root_src_dir}/out/a311d/packages/phone/images/OpenHarmony.img
rm -rf ${root_src_dir}/out/a311d/packages/phone/images/openharmony.conf
rm -rf ${root_src_dir}/out/a311d/packages/phone/images/platform.conf
rm -rf ${root_src_dir}/out/a311d/packages/phone/images/aml_sdc_burn.ini
rm -rf ${root_src_dir}/out/a311d/packages/phone/images/LICENSE
popd
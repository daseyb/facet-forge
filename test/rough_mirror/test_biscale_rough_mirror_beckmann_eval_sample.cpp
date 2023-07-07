/*
 * Copyright (c) <2023> NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <bsdfs/mirror.h>
#include <bsdfs/microsurface.h>
#include <bsdfs/NDFs/beckmann.h>
#include <testing/compare_eval_sample.h>

int main(int argc, char **argv)
{
    srand48(time(NULL));

    if (argc != 6)
    {
        std::cout << "usage: testmirror roughx roughy theta_i numsamplesSample numsamplesEval \n";
        exit(-1);
    }

    const float rough_x = StringToNumber<float>(std::string(argv[1]));
    const float rough_y = StringToNumber<float>(std::string(argv[2]));
    const float theta_i = StringToNumber<float>(std::string(argv[3]));
    size_t numsamplesSample = StringToNumber<size_t>(std::string(argv[4]));
    size_t numsamplesEval = StringToNumber<size_t>(std::string(argv[5]));

    MirrorBRDF micro_brdf;
    BeckmannNDF ndf(&micro_brdf, rough_x, rough_y);
    Microsurface brdf(&ndf);
    BeckmannNDF ndf2(&brdf, rough_x, rough_y);
    Microsurface brdf2(&ndf2);

    compareEvalSample(brdf2, theta_i, numsamplesSample, numsamplesEval, 1.0, 1.0);

    return 1;
}
#include <modules/quaternions/UTQuaternion.hpp>
#include <geometry/quaternions/Quaternion.hpp>
#include <Math.hpp>
#include <string>
#include <iostream>

#include <utils/Chrono.hpp>

using namespace Mind ;

namespace UTMind {
    void UTQuaternion::runTests() {
        allocation() ;
        utilities() ;
        operators() ;
    }

    void UTQuaternion::allocation() {
        // Default.
        {
            Quaternion q1 ;
            Scalar roll, pitch, yaw ;
            q1.to(roll, pitch, yaw) ;
            check(roll == 0.f) ;
            check(pitch == 0.f) ;
            check(yaw == 0.f) ;
        }

        // Values.
        {
            Scalar x = 0.478f ;
            Scalar y = -0.3784f ;
            Scalar z = 0.92f ;
            Scalar w = -0.004f ;
            Quaternion q2(x, y, z, w) ;
            check(q2[Quaternion::Axis::X] == x) ;
            check(q2[Quaternion::Axis::Y] == y) ;
            check(q2[Quaternion::Axis::Z] == z) ;
            check(q2[Quaternion::Axis::W] == w) ;
        }

        // Rotation matrix.
        {
            Matrix3x3f matrix ;
            matrix.at(0,0, +0.8f) ;
            matrix.at(0,1, +0.1f) ;
            matrix.at(0,2, -0.5f) ;
            matrix.at(1,0, +0.7f) ;
            matrix.at(1,1, -1.0f) ;
            matrix.at(1,2, +0.6f) ;
            matrix.at(2,0, +0.0f) ;
            matrix.at(2,1, -0.1f) ;
            matrix.at(2,2, +0.7f) ;

            /*
            Octave result:
            q2 = 0.6124 - 0.2858i - 0.2041j + 0.2449k
            */
            Scalar expectedX = -0.285773803324704 ;
            Scalar expectedY = -0.204124145231932 ;
            Scalar expectedZ =  0.244948974278318 ;
            Scalar expectedW =  0.612372435695794 ;

            Quaternion q3(matrix) ;
            check(compare(q3[Quaternion::Axis::X], expectedX)) ;
            check(compare(q3[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q3[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q3[Quaternion::Axis::W], expectedW)) ;

            Quaternion q4(q3) ;
            check(compare(q4[Quaternion::Axis::X], expectedX)) ;
            check(compare(q4[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q4[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q4[Quaternion::Axis::W], expectedW)) ;
        }

        // Axis and rotation.
        {
            Vector3f axis(0.f, 0.5f, 0.78f) ;
            axis.normalize() ;
            Scalar angle = Math::Pi / 4.f ;

            /*
            Octave result:
            q5 = 0.9239 + 0i + 0.2065j + 0.3222k
            */
            Scalar expectedX =  0.f ;
            Scalar expectedY =  0.206521281112347 ;
            Scalar expectedZ =  0.322173198535262 ;
            Scalar expectedW =  0.923879532511287 ;

            Quaternion q5(axis, angle) ;
            check(compare(q5[Quaternion::Axis::X], expectedX)) ;
            check(compare(q5[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q5[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q5[Quaternion::Axis::W], expectedW)) ;
        }

        // @TODO: Check constructor from 3 axes.

        // Constructor from Euler angles.
        {
            Scalar roll = 6.97f ;
            Scalar pitch = -65.2f ;
            Scalar yaw = -0.274f ;

            Scalar expectedX =  0.0524961f ;
            Scalar expectedY = -0.53765f ;
            Scalar expectedZ =  0.0307396f ;
            Scalar expectedW =  0.84097f ;

            Quaternion q7(roll, pitch, yaw) ;
            check(compare(q7[Quaternion::Axis::X], expectedX)) ;
            check(compare(q7[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q7[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q7[Quaternion::Axis::W], expectedW)) ;

            Quaternion q8 ;
            q8.from(roll, pitch, yaw) ;
            check(compare(q8[Quaternion::Axis::X], expectedX)) ;
            check(compare(q8[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q8[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q8[Quaternion::Axis::W], expectedW)) ;
        }
    }

    void UTQuaternion::utilities() {
        // Dot product and norm.
        {
            Quaternion q1(0.24f, 0.9f, -0.47f, 0.17f) ;
            Quaternion q2(-0.21f, 0.78f, 0.01f, 0.98f) ;
            Scalar dot = q1.dot(q2) ;

            Scalar expectedDot = 0.8135f ;
            check(compare(dot, expectedDot)) ;

            Scalar normQ1 = q1.norm() ;
            Scalar expectedNorm = 1.05707142615814f ;
            check(compare(normQ1, expectedNorm)) ;
        }

        // Normalize.
        {
            Quaternion q3(0.2f, 0.9f, 0.4f, 0.5f) ;
            q3.normalize() ;

            /*
            Octave result:
            >> q3n = unit(q3)
            q3n = 0.4454 + 0.1782i + 0.8018j + 0.3563k
            */
            Scalar expectedX = 0.178174161274950f ;
            Scalar expectedY = 0.801783725737273f ;
            Scalar expectedZ = 0.356348322549899f ;
            Scalar expectedW = 0.445435403187374f ;

            check(compare(q3[Quaternion::Axis::X], expectedX)) ;
            check(compare(q3[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q3[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q3[Quaternion::Axis::W], expectedW)) ;
        }

        // Inverse.
        {
            Quaternion q4(0.96f, -0.7f, 0.39f, 0.f) ;
            Quaternion q4inv = q4.inverse() ;

            /*
             Octave result:
             >> q4inv = inv(q4)
             q4inv = 0 - 0.6139i + 0.4477j - 0.2494k
            */
            Scalar expectedX = -0.613928502909765f ;
            Scalar expectedY =  0.447656200038371f ;
            Scalar expectedZ = -0.249408454307092f ;
            Scalar expectedW =  0.f ;

            check(compare(q4inv[Quaternion::Axis::X], expectedX)) ;
            check(compare(q4inv[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q4inv[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q4inv[Quaternion::Axis::W], expectedW)) ;
        }

        // Exponential.
        {
            Quaternion q5(-0.01f, 0.97f, 0.144f, -0.987f) ;
            Quaternion q5exp = q5.exp() ;

            /*
            Octave result:
            >> q5exp = exp(q5)
            q5exp = 0.2074 - 0.003158i + 0.3063j + 0.04547k
            */
            Scalar expectedX = -0.00315762103232588f ;
            Scalar expectedY =  0.306289240135610f ;
            Scalar expectedZ =  0.0454697428654927f ;
            Scalar expectedW =  0.207387502635283f ;

            check(compare(q5exp[Quaternion::Axis::X], expectedX)) ;
            check(compare(q5exp[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q5exp[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q5exp[Quaternion::Axis::W], expectedW)) ;
        }

        // Logarithmus naturalis.
        {
            Quaternion q6(-0.014f, -0.17f, 0.874f, 0.24f) ;
            Quaternion q6ln = q6.ln() ;

            /*
             Octave result:
             >> q6ln = log(q6)
             q6ln = -0.08092 - 0.02056i - 0.2496j + 1.283k
             But, according to Neil Dantam, W is simplified to 0.
             http://www.neil.dantam.name/note/dantam-quaternion.pdf

             The same result on the W component is seen on the Matlab
             documentation:
             for q=[cos(theta),sin(theta)v], with log(q)=[0,thetav].
             https://fr.mathworks.com/help/aerotbx/ug/quatlog.html
             */
             Scalar expectedX = -0.0205566850320550f ;
             Scalar expectedY = -0.249616889674954f ;
             Scalar expectedZ =  1.28332447985829f ;
             Scalar expectedW =  0.f ;

             check(compare(q6ln[Quaternion::Axis::X], expectedX)) ;
             check(compare(q6ln[Quaternion::Axis::Y], expectedY)) ;
             check(compare(q6ln[Quaternion::Axis::Z], expectedZ)) ;
             check(compare(q6ln[Quaternion::Axis::W], expectedW)) ;
        }

        // SLERP.
        {
            bool isShortestPath = true ;
            Quaternion q7a(0.78f, -0.103f, -0.19f, 0.7409f) ;
            q7a.normalize() ;

            Quaternion q7b(1.f, -0.741f, 0.98f, -0.05f) ;
            q7b.normalize() ;

            Quaternion q7_32slerp = Quaternion::slerp(0.32, q7a, q7b, isShortestPath) ;

            {
                /*
                 Values from Unity (no method in Octave for SLERP...).
                */
                Scalar expectedX =  0.8087177f ;
                Scalar expectedY = -0.2611156f ;
                Scalar expectedZ =  0.1130936f ;
                Scalar expectedW =  0.5147855f ;

                check(compare(q7_32slerp[Quaternion::Axis::X], expectedX)) ;
                check(compare(q7_32slerp[Quaternion::Axis::Y], expectedY)) ;
                check(compare(q7_32slerp[Quaternion::Axis::Z], expectedZ)) ;
                check(compare(q7_32slerp[Quaternion::Axis::W], expectedW)) ;
            }


            Quaternion q7_78slerp = Quaternion::slerp(0.78, q7a, q7b, isShortestPath) ;

            {
                /*
                 Values from Unity (no method in Octave for SLERP...).
                */
                Scalar expectedX =  0.7437601f ;
                Scalar expectedY = -0.4300286f ;
                Scalar expectedZ =  0.485557f ;
                Scalar expectedW =  0.1616511f ;

                check(compare(q7_78slerp[Quaternion::Axis::X], expectedX)) ;
                check(compare(q7_78slerp[Quaternion::Axis::Y], expectedY)) ;
                check(compare(q7_78slerp[Quaternion::Axis::Z], expectedZ)) ;
                check(compare(q7_78slerp[Quaternion::Axis::W], expectedW)) ;
            }
        }

        // NLERP.
        {
            bool isShortestPath = true ;
            Quaternion q8a(-0.274f, 0.35f, -0.279f, 0.2999f) ;
            q8a.normalize() ;

            Quaternion q8b(-0.68f, -0.107f, 0.08f, 0.911f) ;
            q8b.normalize() ;

            Quaternion q8_43nlerp = Quaternion::nlerp(0.43f, q8a, q8b, isShortestPath) ;

            {
                /*
                 Values from Ogre3D (no method in Octave for NLERP...).
                */
                Scalar expectedX = -0.577006f ;
                Scalar expectedY =  0.32549f ;
                Scalar expectedZ = -0.261695f ;
                Scalar expectedW =  0.70188f ;

                check(compare(q8_43nlerp[Quaternion::Axis::X], expectedX)) ;
                check(compare(q8_43nlerp[Quaternion::Axis::Y], expectedY)) ;
                check(compare(q8_43nlerp[Quaternion::Axis::Z], expectedZ)) ;
                check(compare(q8_43nlerp[Quaternion::Axis::W], expectedW)) ;
            }


            Quaternion q8_68nlerp = Quaternion::nlerp(0.68f, q8a, q8b, isShortestPath) ;

            {
                /*
                 Values from Ogre3D (no method in Octave for NLERP...).
                */
                Scalar expectedX = -0.607693f ;
                Scalar expectedY =  0.134732f ;
                Scalar expectedZ = -0.110882f ;
                Scalar expectedW =  0.774765f ;

                check(compare(q8_68nlerp[Quaternion::Axis::X], expectedX)) ;
                check(compare(q8_68nlerp[Quaternion::Axis::Y], expectedY)) ;
                check(compare(q8_68nlerp[Quaternion::Axis::Z], expectedZ)) ;
                check(compare(q8_68nlerp[Quaternion::Axis::W], expectedW)) ;
            }
        }

        // Swap.
        {
            Scalar q9a_x = 0.1f ;
            Scalar q9a_y = 0.2f ;
            Scalar q9a_z = 0.3f ;
            Scalar q9a_w = 0.4f ;
            Quaternion q9a(q9a_x, q9a_y, q9a_z, q9a_w) ;

            Scalar q9b_x = 0.5f ;
            Scalar q9b_y = 0.6f ;
            Scalar q9b_z = 0.7f ;
            Scalar q9b_w = 0.8f ;
            Quaternion q9b(q9b_x, q9b_y, q9b_z, q9b_w) ;

            q9a.swap(q9b) ;

            check(q9a[Quaternion::Axis::X] == q9b_x) ;
            check(q9a[Quaternion::Axis::Y] == q9b_y) ;
            check(q9a[Quaternion::Axis::Z] == q9b_z) ;
            check(q9a[Quaternion::Axis::W] == q9b_w) ;

            check(q9b[Quaternion::Axis::X] == q9a_x) ;
            check(q9b[Quaternion::Axis::Y] == q9a_y) ;
            check(q9b[Quaternion::Axis::Z] == q9a_z) ;
            check(q9b[Quaternion::Axis::W] == q9a_w) ;
        }

        // Closeness.
        {
            Quaternion nearA(0.278f, -0.456f, 0.755f, -0.38f) ;
            nearA.normalize() ;
            Quaternion nearB(-0.281f, 0.455f, -0.756f, 0.382f) ;
            nearB.normalize() ;

            check(nearA.closeTo(nearB, 1e-2f)) ;
            check(nearB.closeTo(nearA, 1e-2f)) ;
            check(!nearA.closeTo(nearB, 1e-3f)) ;
            check(!nearB.closeTo(nearA, 1e-3f)) ;

            Quaternion far(0.713f, -0.188f, 0.178f, 0.651f) ;
            far.normalize() ;
            check(!nearA.closeTo(far, 1e-2f)) ;
            check(!far.closeTo(nearA, 1e-2f)) ;
            check(!nearB.closeTo(far, 1e-2f)) ;
            check(!far.closeTo(nearB, 1e-2f)) ;
        }
    }

    void UTQuaternion::operators() {
        // Access.
        {
            // Variable quaternion.
            Scalar varQ_x = 0.9f ;
            Scalar varQ_y = 0.5f ;
            Scalar varQ_z = 0.7f ;
            Scalar varQ_w = 0.0f ;
            Quaternion varQ(varQ_x, varQ_y, varQ_z, varQ_w) ;

            check(varQ[Quaternion::Axis::X] == varQ_x) ;
            check(varQ[Quaternion::Axis::Y] == varQ_y) ;
            check(varQ[Quaternion::Axis::Z] == varQ_z) ;
            check(varQ[Quaternion::Axis::W] == varQ_w) ;

            varQ[Quaternion::Axis::W] = varQ_z ;
            check(varQ[Quaternion::Axis::W] == varQ_z) ;

            // Constant quaternion.
            Scalar constQ_x = 0.7f ;
            Scalar constQ_y = 0.1f ;
            Scalar constQ_z = 0.5f ;
            Scalar constQ_w = 0.9f ;
            const Quaternion constQ(constQ_x, constQ_y, constQ_z, constQ_w) ;

            check(constQ[Quaternion::Axis::X] == constQ_x) ;
            check(constQ[Quaternion::Axis::Y] == constQ_y) ;
            check(constQ[Quaternion::Axis::Z] == constQ_z) ;
            check(constQ[Quaternion::Axis::W] == constQ_w) ;
        }

        // Affectation.
        {
            Scalar origQ_x = 0.9f ;
            Scalar origQ_y = 0.5f ;
            Scalar origQ_z = 0.7f ;
            Scalar origQ_w = 0.0f ;
            Quaternion origQ(origQ_x, origQ_y, origQ_z, origQ_w) ;

            Quaternion copyQ = origQ ;
            check(copyQ[Quaternion::Axis::X] == origQ_x) ;
            check(copyQ[Quaternion::Axis::Y] == origQ_y) ;
            check(copyQ[Quaternion::Axis::Z] == origQ_z) ;
            check(copyQ[Quaternion::Axis::W] == origQ_w) ;

            check(origQ[Quaternion::Axis::X] == origQ_x) ;
            check(origQ[Quaternion::Axis::Y] == origQ_y) ;
            check(origQ[Quaternion::Axis::Z] == origQ_z) ;
            check(origQ[Quaternion::Axis::W] == origQ_w) ;
        }

        // Sum.
        {
            Quaternion qa(-0.8f, -0.2f, 0.9f, 0.2f) ;
            Quaternion qb(-0.5f, 0.2f, 0.7f, -0.1f) ;
            Quaternion qr = qa + qb ;

            /*
            Octave result (commutative):
            >> qr = qa + qb
            qr = 0.1 - 1.3i + 0j + 1.6k
            */
            Scalar expectedX = -1.3f ;
            Scalar expectedY =  0.f ;
            Scalar expectedZ =  1.6f ;
            Scalar expectedW =  0.1f ;

            check(compare(qr[Quaternion::Axis::X], expectedX)) ;
            check(compare(qr[Quaternion::Axis::Y], expectedY)) ;
            check(compare(qr[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(qr[Quaternion::Axis::W], expectedW)) ;
            qr = qb + qa ;
            check(compare(qr[Quaternion::Axis::X], expectedX)) ;
            check(compare(qr[Quaternion::Axis::Y], expectedY)) ;
            check(compare(qr[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(qr[Quaternion::Axis::W], expectedW)) ;
            qa += qb ;
            check(compare(qa[Quaternion::Axis::X], expectedX)) ;
            check(compare(qa[Quaternion::Axis::Y], expectedY)) ;
            check(compare(qa[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(qa[Quaternion::Axis::W], expectedW)) ;
        }

        // Difference / Negate.
        {
            Quaternion qa(-0.8f, -0.2f, 0.9f, 0.2f) ;
            Quaternion qb(-0.5f, 0.2f, 0.7f, -0.1f) ;
            Quaternion qr = qa - qb ;

            {
                /*
                Octave result:
                >> qr = qa - qb
                qr = 0.3 - 0.3i - 0.4j + 0.2k
                */
                Scalar expectedX = -0.3f ;
                Scalar expectedY = -0.4f ;
                Scalar expectedZ =  0.2f ;
                Scalar expectedW =  0.3f ;

                check(compare(qr[Quaternion::Axis::X], expectedX)) ;
                check(compare(qr[Quaternion::Axis::Y], expectedY)) ;
                check(compare(qr[Quaternion::Axis::Z], expectedZ)) ;
                check(compare(qr[Quaternion::Axis::W], expectedW)) ;

                Quaternion copyQa = qa ;
                copyQa -= qb ;
                check(compare(copyQa[Quaternion::Axis::X], expectedX)) ;
                check(compare(copyQa[Quaternion::Axis::Y], expectedY)) ;
                check(compare(copyQa[Quaternion::Axis::Z], expectedZ)) ;
                check(compare(copyQa[Quaternion::Axis::W], expectedW)) ;
            }

            {
                /*
                Octave result:
                >> qr = qr - qa
                qr = -0.3 + 0.3i + 0.4j - 0.2k
                */
                Scalar expectedX =  0.3f ;
                Scalar expectedY =  0.4f ;
                Scalar expectedZ = -0.2f ;
                Scalar expectedW = -0.3f ;

                qr = qb - qa ;
                check(compare(qr[Quaternion::Axis::X], expectedX)) ;
                check(compare(qr[Quaternion::Axis::Y], expectedY)) ;
                check(compare(qr[Quaternion::Axis::Z], expectedZ)) ;
                check(compare(qr[Quaternion::Axis::W], expectedW)) ;

                qr = -qr ;
                check(compare(qr[Quaternion::Axis::X], -expectedX)) ;
                check(compare(qr[Quaternion::Axis::Y], -expectedY)) ;
                check(compare(qr[Quaternion::Axis::Z], -expectedZ)) ;
                check(compare(qr[Quaternion::Axis::W], -expectedW)) ;
            }
        }

        // Scalar product of quaternion.
        {
            Quaternion q(0.2f, 0.8f, -0.4f, 0.7f) ;
            Scalar product = 0.8f ;
            Quaternion qr = q * product ;

            /*
            Octave result:
            >> qr = 0.8 * q
            qr = 0.56 + 0.16i + 0.64j - 0.32k
            */
            Scalar expectedX =  0.16f ;
            Scalar expectedY =  0.64f ;
            Scalar expectedZ = -0.32f ;
            Scalar expectedW =  0.56f ;

            check(compare(qr[Quaternion::Axis::X], expectedX)) ;
            check(compare(qr[Quaternion::Axis::Y], expectedY)) ;
            check(compare(qr[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(qr[Quaternion::Axis::W], expectedW)) ;

            q *= product ;

            check(compare(q[Quaternion::Axis::X], expectedX)) ;
            check(compare(q[Quaternion::Axis::Y], expectedY)) ;
            check(compare(q[Quaternion::Axis::Z], expectedZ)) ;
            check(compare(q[Quaternion::Axis::W], expectedW)) ;
        }

        // Quaternion product.
        {
            Quaternion qa(-0.47f, 0.1474f, 0.657f, 0.24f) ;
            Quaternion qb(-0.24f, 0.3f, -0.176f, -0.709f) ;

            {
                Quaternion qr = qa * qb ;

                /*
                Octave result:
                >> qr = qa .* qb
                qr = -0.2115 + 0.05259i - 0.2729j - 0.6137k
                */
                Scalar expectedX =  0.0525876f ;
                Scalar expectedY = -0.2729066f ;
                Scalar expectedZ = -0.613677f ;
                Scalar expectedW = -0.211548f ;

                check(compare(qr[Quaternion::Axis::X], expectedX)) ;
                check(compare(qr[Quaternion::Axis::Y], expectedY)) ;
                check(compare(qr[Quaternion::Axis::Z], expectedZ)) ;
                check(compare(qr[Quaternion::Axis::W], expectedW)) ;

                Quaternion copyQa = qa ;
                copyQa *= qb ;
                check(compare(copyQa[Quaternion::Axis::X], expectedX)) ;
                check(compare(copyQa[Quaternion::Axis::Y], expectedY)) ;
                check(compare(copyQa[Quaternion::Axis::Z], expectedZ)) ;
                check(compare(copyQa[Quaternion::Axis::W], expectedW)) ;
            }

            {
                Quaternion qr = qb * qa ;

                /*
                Octave result:
                >> qr = qb .* qa
                qr = -0.2115 + 0.4987i + 0.2079j - 0.4024k
                */
                Scalar expectedX =  0.4986724f ;
                Scalar expectedY =  0.2078934f ;
                Scalar expectedZ = -0.402429f ;
                Scalar expectedW = -0.211548f ;

                check(compare(qr[Quaternion::Axis::X], expectedX)) ;
                check(compare(qr[Quaternion::Axis::Y], expectedY)) ;
                check(compare(qr[Quaternion::Axis::Z], expectedZ)) ;
                check(compare(qr[Quaternion::Axis::W], expectedW)) ;
            }
        }

        // Vector rotation by product with a quaternion.
        {
            Vector3f vec(1.f, 0.f, 0.f) ;
            Quaternion q(-0.813f, 0.481f, 0.201f, 0.258f) ;
            Vector3f rotatedVec = q * vec ;

            /*
             Values from Ogre3D (no method in Octave for vector rotation...).
            */
            Scalar expectedX =  0.456476f ;
            Scalar expectedY = -0.67839f ;
            Scalar expectedZ = -0.575022f ;

            check(compare(rotatedVec.get(Point3Df::Axis::X), expectedX)) ;
            check(compare(rotatedVec.get(Point3Df::Axis::Y), expectedY)) ;
            check(compare(rotatedVec.get(Point3Df::Axis::Z), expectedZ)) ;
        }

        // Test quaternions are equal or different.
        {
            Quaternion qa1(-0.47f, 0.1474f, 0.657f, 0.24f) ;
            Quaternion qa2(-0.47f, 0.1474f, 0.657f, 0.24f) ;
            Quaternion qa3 = qa1 ;

            Quaternion qb1(-0.24f, 0.3f, -0.176f, -0.709f) ;
            Quaternion qb2(-0.24f, 0.3f, -0.176f, -0.709f) ;
            Quaternion qb3 = qb1 ;

            check(qa1 == qa2) ;
            check(qa1 == qa3) ;
            check(qa2 == qa3) ;

            check(qb1 == qb2) ;
            check(qb1 == qb3) ;
            check(qb2 == qb3) ;

            check(qa1 != qb1) ;
            check(qa1 != qb2) ;
            check(qa1 != qb3) ;
        }
    }
}

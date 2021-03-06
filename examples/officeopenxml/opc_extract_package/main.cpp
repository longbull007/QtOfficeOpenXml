/****************************************************************************
**
** Copyright (C) 2014-2015 Debao Zhang <hello@debao.me>
**
** This file is part of the QtOfficeOpenXml library.
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPLv2 included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
****************************************************************************/

#include <QtOfficeOpenXml>
#include <QtWidgets>
#include <iostream>

using namespace QtOfficeOpenXml;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QString fileName = QFileDialog::getOpenFileName( 0, "Open OPC Package", "", "Office files (*.xlsx *.docx *.pptx);;All files(*.*)");
    if (fileName.isEmpty())
        return -1;

    Opc::Package *package = Opc::Package::open(fileName, QIODevice::ReadOnly);
    if (!package) {
        std::cerr << qPrintable(QString("Fail to open the package %1").arg(fileName)) << std::endl;
        return -2;
    }

    //print root relationships
    foreach (Opc::PackageRelationship *relation, package->relationships()) {
        std::cout << "\t" << qPrintable(relation->id()) << "\t"
                  << qPrintable(relation->target()) << std::endl;
    }

    //print part and part relationships
    foreach (Opc::PackagePart *part, package->parts()) {
        std::cout << qPrintable(part->partName()) << std::endl;
        foreach (Opc::PackageRelationship *relation, part->relationships()) {
            std::cout << "\t" << qPrintable(relation->id()) << "\t"
                      << qPrintable(relation->target()) << std::endl;
        }
    }

    return 0;
}
